<?php
/**
 * Activity 2 helper — validate an XML file against students.xsd.
 *
 * CLI usage:
 *     php validate.php                  # validates students.xml
 *     php validate.php students_invalid.xml
 *
 * Exit code 0 = valid, 1 = invalid. Errors are printed with line numbers.
 */

$xmlFile = $argv[1] ?? __DIR__ . '/students.xml';
$xsdFile = __DIR__ . '/students.xsd';

if (!is_file($xmlFile)) {
    fwrite(STDERR, "XML file not found: $xmlFile\n");
    exit(1);
}

// Collect libxml errors instead of dumping raw warnings.
libxml_use_internal_errors(true);

$doc = new DOMDocument();
if (!$doc->load($xmlFile)) {
    echo "NOT WELL-FORMED: $xmlFile\n";
    foreach (libxml_get_errors() as $error) {
        echo "  line {$error->line}: " . trim($error->message) . "\n";
    }
    exit(1);
}

if ($doc->schemaValidate($xsdFile)) {
    echo "VALID: " . basename($xmlFile) . " conforms to " . basename($xsdFile) . "\n";
    exit(0);
}

echo "INVALID: " . basename($xmlFile) . " violates " . basename($xsdFile) . "\n";
foreach (libxml_get_errors() as $error) {
    echo "  line {$error->line}: " . trim($error->message) . "\n";
}
libxml_clear_errors();
exit(1);
