<?php

include "adminAuth.php";
include "db.php";

if($_SERVER["REQUEST_METHOD"]=="POST")
{

$id=$_POST["id"];
$name=trim($_POST["name"]);
$price=$_POST["price"];

$stmt=$conn->prepare("UPDATE products SET name=?, price=? WHERE id=?");

$stmt->bind_param("sdi",$name,$price,$id);

if($stmt->execute())
{
    echo "Product Updated Successfully.<br><br>";
}
else
{
    echo "Update Failed.<br><br>";
}

echo "<a href='admin.php'>Back</a>";

}

?>