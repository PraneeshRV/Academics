<?php

function calculateTotal(array $marks): int {
    $total = 0;
    foreach ($marks as $mark) {
        $total += $mark;
    }
    return $total;
}

function calculateAverage(array $marks): float {
    $total = calculateTotal($marks);
    return $total / count($marks);
}

function findHighest(array $marks): int {
    return max($marks);
}


function findLowest(array $marks): int {
    return min($marks);
}

function assignGrade(float $average): string {
    if ($average >= 90) {
        return 'A';
    } elseif ($average >= 80) {
        return 'B';
    } elseif ($average >= 70) {
        return 'C';
    } elseif ($average >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

function resultStatus(array $marks): string {
    foreach ($marks as $mark) {
        if ($mark < 35) {
            return 'Fail';
        }
    }
    return 'Pass';
}

$submitted   = false;
$studentName = '';
$marks       = [];
$total       = 0;
$average     = 0;
$grade       = '';
$status      = '';
$highest     = 0;
$lowest      = 0;
$error       = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $studentName = trim($_POST['student_name'] ?? '');
    $mark1 = $_POST['mark1'] ?? '';
    $mark2 = $_POST['mark2'] ?? '';
    $mark3 = $_POST['mark3'] ?? '';

    if ($studentName === '' || $mark1 === '' || $mark2 === '' || $mark3 === '') {
        $error = 'Please fill in the student name and all three marks.';
    } elseif (!is_numeric($mark1) || !is_numeric($mark2) || !is_numeric($mark3)) {
        $error = 'Marks must be numeric values.';
    } else {
        $marks = [(int)$mark1, (int)$mark2, (int)$mark3];

        $total   = calculateTotal($marks);
        $average = calculateAverage($marks);
        $grade   = assignGrade($average);
        $status  = resultStatus($marks);
        $highest = findHighest($marks);
        $lowest  = findLowest($marks);

        $submitted = true;
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Student Grade Calculator</title>
<style>
    body { font-family: Arial, sans-serif; background: #f4f6f8; margin: 0; padding: 40px 20px; }
    .card { max-width: 480px; margin: 0 auto; background: #fff; border-radius: 8px;
            padding: 30px; box-shadow: 0 2px 8px rgba(0,0,0,0.1); }
    h1 { font-size: 22px; margin-top: 0; color: #2c3e50; }
    label { display: block; margin-top: 14px; font-weight: bold; color: #34495e; font-size: 14px; }
    input[type=text], input[type=number] {
        width: 100%; padding: 8px; margin-top: 4px; box-sizing: border-box;
        border: 1px solid #ccc; border-radius: 4px; font-size: 14px;
    }
    button {
        margin-top: 20px; width: 100%; padding: 10px; background: #2980b9; color: #fff;
        border: none; border-radius: 4px; font-size: 15px; cursor: pointer;
    }
    button:hover { background: #1f6690; }
    .error { color: #c0392b; margin-top: 12px; font-size: 14px; }
    .result { margin-top: 25px; padding: 18px; background: #ecf6ff; border-left: 4px solid #2980b9;
              border-radius: 4px; font-size: 15px; line-height: 1.8; }
    .result strong { color: #2c3e50; }
    .pass { color: #27ae60; font-weight: bold; }
    .fail { color: #c0392b; font-weight: bold; }
</style>
</head>
<body>
<div class="card">
    <h1>Student Grade Calculator</h1>

    <form method="POST" action="">
        <label for="student_name">Student Name</label>
        <input type="text" id="student_name" name="student_name"
               value="<?= htmlspecialchars($studentName) ?>" required>

        <label for="mark1">Mark 1 (Subject 1)</label>
        <input type="number" id="mark1" name="mark1" min="0" max="100"
               value="<?= htmlspecialchars($_POST['mark1'] ?? '') ?>" required>

        <label for="mark2">Mark 2 (Subject 2)</label>
        <input type="number" id="mark2" name="mark2" min="0" max="100"
               value="<?= htmlspecialchars($_POST['mark2'] ?? '') ?>" required>

        <label for="mark3">Mark 3 (Subject 3)</label>
        <input type="number" id="mark3" name="mark3" min="0" max="100"
               value="<?= htmlspecialchars($_POST['mark3'] ?? '') ?>" required>

        <button type="submit">Calculate Grade</button>
    </form>

    <?php if ($error): ?>
        <div class="error"><?= htmlspecialchars($error) ?></div>
    <?php endif; ?>

    <?php if ($submitted): ?>
        <div class="result">
            <strong>Student Name</strong> : <?= htmlspecialchars($studentName) ?><br>
            <strong>Marks</strong> : <?= implode(', ', $marks) ?><br>
            <strong>Total</strong> : <?= $total ?><br>
            <strong>Average</strong> : <?= number_format($average, 2) ?><br>
            <strong>Grade</strong> : <?= $grade ?><br>
            <strong>Highest Mark</strong> : <?= $highest ?><br>
            <strong>Lowest Mark</strong> : <?= $lowest ?><br>
            <strong>Result</strong> :
            <span class="<?= $status === 'Pass' ? 'pass' : 'fail' ?>"><?= $status ?></span>
        </div>
    <?php endif; ?>
</div>
</body>
</html>
