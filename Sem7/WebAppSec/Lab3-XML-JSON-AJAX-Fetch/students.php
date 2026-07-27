<?php
/**
 * Backend for Activity 4 (AJAX) and Activity 5 (Fetch API).
 * Returns an array of five students as JSON.
 */

header("Content-Type: application/json");

$students = [
    ["registerNumber" => "CB22001", "name" => "Alice Thomas",        "department" => "CSE", "semester" => 5, "cgpa" => 8.92],
    ["registerNumber" => "CB22002", "name" => "Bharath Kumar",       "department" => "CSE", "semester" => 5, "cgpa" => 9.14],
    ["registerNumber" => "CB22003", "name" => "Divya Ramesh",        "department" => "IT",  "semester" => 6, "cgpa" => 8.45],
    ["registerNumber" => "CB22004", "name" => "Karthik Subramanian", "department" => "ECE", "semester" => 7, "cgpa" => 7.86],
    ["registerNumber" => "CB22005", "name" => "Meera Nair",          "department" => "CSE", "semester" => 5, "cgpa" => 9.35],
];

echo json_encode($students);
