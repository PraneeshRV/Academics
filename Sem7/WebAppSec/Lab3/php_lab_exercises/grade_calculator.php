<?php
require 'auth_check.php';

function calculateTotal(array $marks): float
{
    return array_sum($marks);
}

function calculateAverage(array $marks): float
{
    return calculateTotal($marks) / count($marks);
}

function calculateGrade(float $average): string
{
    if ($average >= 90) return 'A';
    if ($average >= 75) return 'B';
    if ($average >= 60) return 'C';
    if ($average >= 40) return 'D';
    return 'F';
}

function isPass(array $marks, float $passMark = 40): bool
{
    foreach ($marks as $mark) {
        if ($mark < $passMark) {
            return false;
        }
    }
    return true;
}

$result = null;
$error = '';
$posted = ['mark1' => '', 'mark2' => '', 'mark3' => ''];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $posted['mark1'] = $_POST['mark1'] ?? '';
    $posted['mark2'] = $_POST['mark2'] ?? '';
    $posted['mark3'] = $_POST['mark3'] ?? '';

    if (!is_numeric($posted['mark1']) || !is_numeric($posted['mark2']) || !is_numeric($posted['mark3'])) {
        $error = 'All marks must be numeric.';
    } else {
        $marks = [(float)$posted['mark1'], (float)$posted['mark2'], (float)$posted['mark3']];
        foreach ($marks as $mark) {
            if ($mark < 0 || $mark > 100) {
                $error = 'Marks must be between 0 and 100.';
                break;
            }
        }
        if ($error === '') {
            $result = [
                'total' => calculateTotal($marks),
                'average' => round(calculateAverage($marks), 2),
                'grade' => calculateGrade(calculateAverage($marks)),
                'highest' => max($marks),
                'lowest' => min($marks),
                'pass' => isPass($marks),
            ];
        }
    }
}
?>
<!DOCTYPE html>
<html>
<head><title>Grade Calculator</title></head>
<body>
<h2>Grade Calculator</h2>
<p>Logged in as: <?= htmlspecialchars($_SESSION['username']) ?></p>

<?php if ($error): ?>
    <p style="color:red;"><?= htmlspecialchars($error) ?></p>
<?php endif; ?>

<form method="post">
    Subject 1: <input type="text" name="mark1" value="<?= htmlspecialchars($posted['mark1']) ?>"><br><br>
    Subject 2: <input type="text" name="mark2" value="<?= htmlspecialchars($posted['mark2']) ?>"><br><br>
    Subject 3: <input type="text" name="mark3" value="<?= htmlspecialchars($posted['mark3']) ?>"><br><br>
    <input type="submit" value="Calculate">
</form>

<?php if ($result): ?>
    <h3>Results</h3>
    <ul>
        <li>Total: <?= htmlspecialchars((string)$result['total']) ?></li>
        <li>Average: <?= htmlspecialchars((string)$result['average']) ?></li>
        <li>Grade: <?= htmlspecialchars($result['grade']) ?></li>
        <li>Highest: <?= htmlspecialchars((string)$result['highest']) ?></li>
        <li>Lowest: <?= htmlspecialchars((string)$result['lowest']) ?></li>
        <li>Status: <?= $result['pass'] ? 'Pass' : 'Fail' ?></li>
    </ul>
<?php endif; ?>

<p><a href="welcome.php">Back</a> | <a href="logout.php">Logout</a></p>
</body>
</html>
