<?php

include "adminAuth.php";
include "db.php";

if($_SERVER["REQUEST_METHOD"]=="POST")
{

$name=trim($_POST["name"]);
$price=$_POST["price"];

if(empty($name) || empty($price))
{
    die("All fields are required.");
}

$stmt=$conn->prepare("INSERT INTO products(name,price) VALUES(?,?)");

$stmt->bind_param("sd",$name,$price);

if($stmt->execute())
{
    echo "Product Added Successfully.<br><br>";
}
else
{
    echo "Failed to Add Product.<br><br>";
}

echo "<a href='admin.php'>Back to Admin Panel</a>";

}

?>