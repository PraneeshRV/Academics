<?php
// calculate.php - Pull marks from DB, compute the grade
require 'db.php';

$email = trim($_POST['email'] ?? '');

if ($email === '') {
    echo "Please enter an email. <a href='index.php'>Back</a>";
    exit;
}

// Get the most recent record for this email
$stmt = $conn->prepare(
    "SELECT subject1, subject2, subject3, subject4, subject5
     FROM marks WHERE email = ? ORDER BY id DESC LIMIT 1"
);
$stmt->bind_param("s", $email);
$stmt->execute();
$result = $stmt->get_result();

if ($row = $result->fetch_assoc()) {
    $total = array_sum($row);   // sum of the 5 subjects
    $avg   = $total / 5;
    $grade = calcGrade($avg);

    echo "<h3>Result for " . htmlspecialchars($email) . "</h3>";
    echo "Total: $total / 500<br>";
    echo "Average: " . number_format($avg, 2) . "%<br>";
    echo "Grade: <strong style='font-size:1.3em'>$grade</strong>";
} else {
    echo "<h3 style='color:red'>No record found for " . htmlspecialchars($email) . "</h3>";
    echo "Upload the XML first.";
}

// Grade rule - adjust the cutoffs to match your rubric
function calcGrade($avg) {
    if ($avg >= 90) return "A+";
    if ($avg >= 80) return "A";
    if ($avg >= 70) return "B";
    if ($avg >= 60) return "C";
    if ($avg >= 50) return "D";
    return "F";
}

$stmt->close();
$conn->close();

echo "<br><br><a href='index.php'>&larr; Back</a>";
?>
