<?php
// upload.php - Validate the XML, then load it into the database
require 'db.php';

$xmlFile = "student.xml";
$xsdFile = "student.xsd";

// Collect libxml errors ourselves instead of printing warnings
libxml_use_internal_errors(true);

$dom = new DOMDocument();

// Step 1: well-formedness check (does it load as valid XML at all?)
if (!$dom->load($xmlFile)) {
    echo "<h3 style='color:red'>XML is NOT well-formed.</h3>";
    foreach (libxml_get_errors() as $e) {
        echo htmlspecialchars(trim($e->message)) . "<br>";
    }
    libxml_clear_errors();
    exit;
}

// Step 2: schema validation against the XSD
if (!$dom->schemaValidate($xsdFile)) {
    echo "<h3 style='color:red'>XML is well-formed but FAILED schema validation.</h3>";
    foreach (libxml_get_errors() as $e) {
        echo htmlspecialchars(trim($e->message)) . "<br>";
    }
    libxml_clear_errors();
    exit;
}

echo "<h3 style='color:green'>&#10004; XML is well-formed and valid against the schema.</h3>";

// Step 3: parse the values
$xml = simplexml_load_file($xmlFile);
$email = (string)$xml->email;

$m = [];
foreach ($xml->marks->subject as $subject) {
    $m[] = (int)$subject;
}

// Step 4: insert into DB using a prepared statement (prevents SQL injection)
$stmt = $conn->prepare(
    "INSERT INTO marks (email, subject1, subject2, subject3, subject4, subject5)
     VALUES (?, ?, ?, ?, ?, ?)"
);
$stmt->bind_param("siiiii", $email, $m[0], $m[1], $m[2], $m[3], $m[4]);

if ($stmt->execute()) {
    echo "Data uploaded to database successfully. Record ID: " . $stmt->insert_id;
} else {
    echo "<span style='color:red'>Insert failed: " . $stmt->error . "</span>";
}

$stmt->close();
$conn->close();

echo "<br><br><a href='index.php'>&larr; Back</a>";
?>
