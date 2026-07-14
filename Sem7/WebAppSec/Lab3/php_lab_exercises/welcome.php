<?php
require 'auth_check.php';
?>
<!DOCTYPE html>
<html>
<head><title>Welcome</title></head>
<body>
<h2>Welcome, <?= htmlspecialchars($_SESSION['username']) ?>!</h2>
<p><a href="grade_calculator.php">Grade Calculator</a></p>
<p><a href="logout.php">Logout</a></p>
</body>
</html>
