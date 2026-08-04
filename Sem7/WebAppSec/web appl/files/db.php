<?php
// db.php - Database connection
// NOTE: port 3307 because your MySQL runs on 3307 (not the default 3306).
// Using 127.0.0.1 (not "localhost") so the port is actually respected.
$host = "127.0.0.1";
$user = "root";
$pass = "";
$dbname = "studentdb";
$port = 3307;
 
$conn = new mysqli($host, $user, $pass, $dbname, $port);
 
if ($conn->connect_error) {
    die("Database connection failed: " . $conn->connect_error);
}
?>