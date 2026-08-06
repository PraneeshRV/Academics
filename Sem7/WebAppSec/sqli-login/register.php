<?php
session_start();
require_once 'db.php';

$error = '';
$success = '';
$executed_sql = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'] ?? '';
    $email = $_POST['email'] ?? '';
    $password = $_POST['password'] ?? '';

    if (empty($username) || empty($password)) {
        $error = 'Username and password are required!';
    } else {
        // Intentionally VULNERABLE SQL Query for educational lab purposes
        $executed_sql = "INSERT INTO users (username, password, email, role) VALUES ('$username', '$password', '$email', 'user')";

        // Execute query directly without prepared statements
        $result = @mysqli_query($conn, $executed_sql);

        if ($result) {
            $success = "Registration successful for user '<b>" . htmlspecialchars($username) . "</b>'! You can now log in.";
        } else {
            $error = "SQL Error: " . mysqli_error($conn);
        }
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register - SQL Injection Lab</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>🔐 SQLi Auth Lab</h1>
            <p>Registration Setup (Intentionally Vulnerable)</p>
        </header>

        <div class="card">
            <h2>Create New Account</h2>

            <?php if ($error): ?>
                <div class="alert alert-danger"><?= $error ?></div>
            <?php endif; ?>

            <?php if ($success): ?>
                <div class="alert alert-success"><?= $success ?></div>
            <?php endif; ?>

            <form action="register.php" method="POST">
                <div class="form-group">
                    <label for="username">Username:</label>
                    <input type="text" id="username" name="username" class="form-control" placeholder="e.g. Charlie or test'--" required>
                </div>

                <div class="form-group">
                    <label for="email">Email Address:</label>
                    <input type="text" id="email" name="email" class="form-control" placeholder="e.g. user@domain.com">
                </div>

                <div class="form-group">
                    <label for="password">Password:</label>
                    <input type="password" id="password" name="password" class="form-control" placeholder="Enter password" required>
                </div>

                <button type="submit" class="btn" style="width: 100%;">Register Account</button>
            </form>

            <?php if (!empty($executed_sql)): ?>
                <div class="query-debug">
                    <h4>Executed SQL Query:</h4>
                    <code><?= htmlspecialchars($executed_sql) ?></code>
                </div>
            <?php endif; ?>

            <div class="cheat-sheet">
                <h4>💡 Educational Tip: Registration Injection</h4>
                <p style="font-size: 0.9rem; color: var(--text-secondary);">
                    Try inserting quotes in the email or username field to observe SQL syntax errors, or craft payloads like <code>admin', 'hackedpass', 'attacker@test.com', 'admin') -- </code> to register yourself directly as an <b>admin</b>!
                </p>
            </div>

            <div class="nav-links">
                Already have an account? <a href="login.php">Log In Here</a>
            </div>
        </div>
    </div>
    <script>
        function fillPayload(username, password) {
            document.getElementById('username').value = username;
            document.getElementById('password').value = password;
        }
    </script>
</body>
</html>
