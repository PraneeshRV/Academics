<?php

// Connect to MySQL server
$conn = mysqli_connect("localhost", "root", "yourpassword", "php_lab");
// Check whether the connection was successful
if(!$conn)
{
    die("Connection failed: " . mysqli_connect_error());
}

echo "Connected to MySQL successfully";

?>
