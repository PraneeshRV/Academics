<?php

include "db.php";

if($_SERVER["REQUEST_METHOD"]=="POST")
{

$username=trim($_POST["username"]);
$email=trim($_POST["email"]);
$password=$_POST["password"];
$role=$_POST["role"];

/* Server Validation */

if(empty($username) || empty($email) || empty($password))
{
die("All fields required");
}

if(!filter_var($email,FILTER_VALIDATE_EMAIL))
{
die("Invalid Email");
}

if(strlen($password)<6)
{
die("Password must be minimum 6 characters");
}

/* Hash Password */

$hash=password_hash($password,PASSWORD_BCRYPT);

/* Prepared Statement */

$stmt=$conn->prepare("INSERT INTO users(username,email,password,role) VALUES(?,?,?,?)");

$stmt->bind_param("ssss",$username,$email,$hash,$role);

if($stmt->execute())
{
echo "Registration Successful<br>";
echo "<a href='login.html'>Login</a>";
}
else
{
echo "Email Already Exists";
}

}
?>