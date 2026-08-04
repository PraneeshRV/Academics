<?php
include "auth.php";
?>

<!DOCTYPE html>
<html>

<head>
    <title>Update Profile</title>
</head>

<body>

<h2>Update Username</h2>

<form action="updateProfile.php" method="POST">

New Username

<br><br>

<input
type="text"
name="username"
required>

<br><br>

<input
type="submit"
value="Update">

</form>

<br>

<a href="home.php">Back</a>

</body>

</html>