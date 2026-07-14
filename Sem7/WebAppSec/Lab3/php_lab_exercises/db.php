<?php

$host = 'localhost';
$dbname = 'grade_system';
$dbuser = 'grade_app';
$dbpass = 'GXfDCnkAuR70piN6lS43VId';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8mb4", $dbuser, $dbpass, [
        PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    ]);
} catch (PDOException $e) {
    die('Connection failed: ' . $e->getMessage());
}
