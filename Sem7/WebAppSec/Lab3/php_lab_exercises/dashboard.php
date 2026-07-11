<?php
session_start();

// If the user is not logged in, send them back to the login page
if(!isset($_SESSION["username"]))
{
    header("Location: login.php");
    exit();
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Dashboard</title>
</head>
<body>

<h2>Welcome, <?php echo $_SESSION["username"]; ?></h2>

<a href="logout.php">Logout</a>

</body>
</html>
