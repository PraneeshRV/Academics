<?php

include "auth.php";
include "db.php";

$username = trim($_POST['username']);

if(empty($username))
{
    die("Username Required");
}

$stmt = $conn->prepare("UPDATE users SET username=? WHERE id=?");

$stmt->bind_param("si",$username,$_SESSION['user_id']);

$stmt->execute();

$_SESSION['username']=$username;

echo "Username Updated Successfully.<br><br>";

echo "<a href='home.php'>Go Home</a>";

?>