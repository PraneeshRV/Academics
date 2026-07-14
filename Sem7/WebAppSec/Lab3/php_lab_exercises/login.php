<?php
if (session_status() !== PHP_SESSION_ACTIVE) {
    session_start();
}
require 'db.php';

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    header('Location: loginform.php');
    exit();
}

$username = trim($_POST['username'] ?? '');
$password = $_POST['password'] ?? '';

$stmt = $pdo->prepare('SELECT * FROM users WHERE username = ?');
$stmt->execute([$username]);
$user = $stmt->fetch();

if ($user && password_verify($password, $user['password'])) {
    $_SESSION['username'] = $user['username'];
    setcookie('username', $user['username'], time() + 7 * 24 * 60 * 60, '/');
    header('Location: welcome.php');
    exit();
}

header('Location: loginform.php?error=' . urlencode('Invalid username or password'));
exit();
