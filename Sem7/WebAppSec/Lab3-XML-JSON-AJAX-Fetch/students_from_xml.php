<?php
/**
 * Challenge Exercise backend.
 *
 * 1. Validates students.xml against students.xsd.
 * 2. Reads the XML with simplexml_load_file().
 * 3. Converts it to JSON with json_encode() and sends it to the browser.
 *
 * On failure it returns HTTP 500 with a JSON error body, so the Fetch
 * front end has something meaningful to display.
 */

header("Content-Type: application/json");

$xmlFile = __DIR__ . '/students.xml';
$xsdFile = __DIR__ . '/students.xsd';

libxml_use_internal_errors(true);

function fail(string $message, array $details = []): never
{
    http_response_code(500);
    echo json_encode(["error" => $message, "details" => $details]);
    exit;
}

if (!is_file($xmlFile)) {
    fail("students.xml not found on the server.");
}

// ---- Step 1: schema validation -------------------------------------------
$doc = new DOMDocument();
if (!$doc->load($xmlFile)) {
    fail("students.xml is not well-formed XML.");
}
if (!$doc->schemaValidate($xsdFile)) {
    $details = [];
    foreach (libxml_get_errors() as $error) {
        $details[] = "line {$error->line}: " . trim($error->message);
    }
    libxml_clear_errors();
    fail("students.xml failed schema validation.", $details);
}

// ---- Step 2: read the XML -------------------------------------------------
$xml = simplexml_load_file($xmlFile);
if ($xml === false) {
    fail("simplexml_load_file() could not read students.xml.");
}

/*
 * Do NOT just call json_encode($xml).
 * SimpleXML would encode every value as a string, and a document with a
 * single <student> would collapse into an object instead of an array.
 * Building a plain PHP array first keeps the types and the shape correct.
 */
$students = [];
foreach ($xml->student as $student) {
    $students[] = [
        "registerNumber" => (string) $student->registerNumber,
        "name"           => (string) $student->name,
        "department"     => (string) $student->department,
        "semester"       => (int)    $student->semester,
        "cgpa"           => (float)  $student->cgpa,
    ];
}

// ---- Step 3: emit JSON ----------------------------------------------------
echo json_encode($students);
