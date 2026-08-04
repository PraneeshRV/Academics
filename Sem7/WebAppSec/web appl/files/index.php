<?php
require 'db.php';

$message   = "";   // validation / status message
$resultHtml = "";  // grade output pulled back from DB

if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $name     = $_POST['name'] ?? '';
    $roll     = $_POST['roll'] ?? '';
    $subNames = $_POST['sub_name'] ?? [];   // array of 5
    $subMarks = $_POST['sub_mark'] ?? [];   // array of 5

    // ---- Build an XML document from the entered data ----
    // Raw interpolation on purpose: if any input breaks XML structure,
    // loadXML() will fail and we report "Not an XML file".
    $xmlString  = '<?xml version="1.0" encoding="UTF-8"?>';
    $xmlString .= '<student>';
    $xmlString .= '<name>' . $name . '</name>';
    $xmlString .= '<roll>' . $roll . '</roll>';
    $xmlString .= '<marks>';
    for ($i = 0; $i < 5; $i++) {
        $sn = $subNames[$i] ?? '';
        $sm = $subMarks[$i] ?? '';
        $xmlString .= '<subject name="' . $sn . '">' . $sm . '</subject>';
    }
    $xmlString .= '</marks></student>';

    // ---- Validation in the background (no upload button) ----
    libxml_use_internal_errors(true);
    $dom = new DOMDocument();

    if (!$dom->loadXML($xmlString)) {
        // Not well-formed -> not valid XML
        $message = "<p class='err'>Not an XML file</p>";
    } elseif (!$dom->schemaValidate('student.xsd')) {
        // Well-formed but breaks the schema (empty fields, mark not 0-100, etc.)
        $message = "<p class='err'>XML is not valid. Marks must be whole numbers 0&ndash;100 and no field may be empty.</p>";
        foreach (libxml_get_errors() as $e) {
            $message .= "<small>" . htmlspecialchars(trim($e->message)) . "</small><br>";
        }
        libxml_clear_errors();
    } else {
        // ---- Valid: store in the database ----
        $stmt = $conn->prepare(
            "INSERT INTO marks
             (name, roll_number,
              sub1_name, sub1_mark, sub2_name, sub2_mark,
              sub3_name, sub3_mark, sub4_name, sub4_mark,
              sub5_name, sub5_mark)
             VALUES (?,?,?,?,?,?,?,?,?,?,?,?)"
        );
        $m = array_map('intval', $subMarks);
        $stmt->bind_param(
            "sssisisisisi",
            $name, $roll,
            $subNames[0], $m[0], $subNames[1], $m[1],
            $subNames[2], $m[2], $subNames[3], $m[3],
            $subNames[4], $m[4]
        );
        $stmt->execute();
        $newId = $stmt->insert_id;
        $stmt->close();

        // ---- Read the row back FROM THE DATABASE and grade it ----
        $res = $conn->query("SELECT * FROM marks WHERE id = " . intval($newId));
        $row = $res->fetch_assoc();
        $resultHtml = renderResult($row);
    }
}

function calcGrade($avg) {
    if ($avg >= 90) return "A+";
    if ($avg >= 80) return "A";
    if ($avg >= 70) return "B";
    if ($avg >= 60) return "C";
    if ($avg >= 50) return "D";
    return "F";
}

function renderResult($row) {
    $names = [$row['sub1_name'],$row['sub2_name'],$row['sub3_name'],$row['sub4_name'],$row['sub5_name']];
    $marks = [$row['sub1_mark'],$row['sub2_mark'],$row['sub3_mark'],$row['sub4_mark'],$row['sub5_mark']];
    $total = array_sum($marks);
    $avg   = $total / 5;
    $grade = calcGrade($avg);

    $h  = "<div class='result'>";
    $h .= "<h3>Result (fetched from database)</h3>";
    $h .= "<b>Name:</b> " . htmlspecialchars($row['name']) . "<br>";
    $h .= "<b>Roll Number:</b> " . htmlspecialchars($row['roll_number']) . "<br><br>";
    $h .= "<table><tr><th>Subject</th><th>Mark</th></tr>";
    for ($i = 0; $i < 5; $i++) {
        $h .= "<tr><td>" . htmlspecialchars($names[$i]) . "</td><td>" . intval($marks[$i]) . "</td></tr>";
    }
    $h .= "</table><br>";
    $h .= "<b>Total:</b> $total / 500<br>";
    $h .= "<b>Average:</b> " . number_format($avg, 2) . "%<br>";
    $h .= "<b>Grade:</b> <span class='grade'>$grade</span>";
    $h .= "</div>";
    return $h;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Student Marks Portal</title>
<style>
    body { font-family: Arial, sans-serif; max-width: 640px; margin: 40px auto; padding: 0 16px; }
    h1 { font-size: 1.5em; }
    label { display:block; font-weight:bold; margin: 12px 0 4px; }
    input { padding: 8px; border: 1px solid #ccc; border-radius: 6px; }
    input[type=text], input[type=number] { width: 240px; }
    .row { display:flex; gap:10px; align-items:center; margin-bottom:6px; }
    .row input.sub { width: 260px; }
    .row input.mark { width: 90px; }
    button { margin-top:16px; padding: 10px 18px; font-size:1em; border:none;
             border-radius:6px; background:#2563eb; color:#fff; cursor:pointer; }
    button:hover { background:#1d4ed8; }
    .err { color:#b91c1c; font-weight:bold; }
    .result { border:1px solid #16a34a; background:#f0fdf4; border-radius:8px; padding:16px; margin-top:20px; }
    table { border-collapse: collapse; }
    td, th { border:1px solid #ccc; padding:6px 12px; text-align:left; }
    .grade { font-size:1.4em; font-weight:bold; }
</style>
</head>
<body>
    <h1>Student Marks Portal</h1>

    <?php if ($message) echo $message; ?>

    <form method="post">
        <label>Name</label>
        <input type="text" name="name" value="<?php echo htmlspecialchars($_POST['name'] ?? ''); ?>" required>

        <label>Roll Number</label>
        <input type="text" name="roll" value="<?php echo htmlspecialchars($_POST['roll'] ?? ''); ?>" required>

        <label>Subjects &amp; Marks (all 5)</label>
        <?php for ($i = 0; $i < 5; $i++): ?>
        <div class="row">
            <input class="sub"  type="text"   name="sub_name[]"  placeholder="Subject <?php echo $i+1; ?> name"
                   value="<?php echo htmlspecialchars($_POST['sub_name'][$i] ?? ''); ?>" required>
            <input class="mark" type="number" name="sub_mark[]"  placeholder="Mark" min="0" max="100"
                   value="<?php echo htmlspecialchars($_POST['sub_mark'][$i] ?? ''); ?>" required>
        </div>
        <?php endfor; ?>

        <button type="submit">Submit &amp; Show Grade</button>
    </form>

    <?php if ($resultHtml) echo $resultHtml; ?>
</body>
</html>