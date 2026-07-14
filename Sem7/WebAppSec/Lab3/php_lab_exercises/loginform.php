<?php
if (session_status() !== PHP_SESSION_ACTIVE) {
    session_start();
}

$username = $_COOKIE['username'] ?? '';
$error = $_GET['error'] ?? '';
?>
<!DOCTYPE html>
<html>
<head><title>Login</title></head>
<body>
<h2>Student Login</h2>

<?php if ($error): ?>
    <p style="color:red;"><?= htmlspecialchars($error) ?></p>
<?php endif; ?>

<form method="post" action="login.php">
    Username: <input type="text" name="username" value="<?= htmlspecialchars($username) ?>"><br><br>
    Password: <input type="password" name="password"><br><br>
    <input type="submit" value="Login">
</form>

</body>
</html>
