<?php

include "adminAuth.php";
include "db.php";

$result=$conn->query("SELECT * FROM products");

$data=array();

while($row=$result->fetch_assoc())
{
    $data[]=$row;
}

header("Content-Type: application/json");

echo json_encode($data);

?>