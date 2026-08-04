<?php

include "adminAuth.php";
include "db.php";

$id=$_GET["id"];

$stmt=$conn->prepare("DELETE FROM products WHERE id=?");

$stmt->bind_param("i",$id);

if($stmt->execute())
{
    echo "Product Deleted Successfully.<br><br>";
}
else
{
    echo "Delete Failed.<br><br>";
}

echo "<a href='admin.php'>Back</a>";

?>