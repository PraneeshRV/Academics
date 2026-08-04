<?php

include("db.php");

libxml_use_internal_errors(true);

$xmlString = $_POST['xml'];

$dom = new DOMDocument();

if (!$dom->loadXML($xmlString)) {

    echo "<h2 style='color:red'>XML is NOT Well Formed</h2>";

    foreach(libxml_get_errors() as $error){
        echo $error->message."<br>";
    }

    exit();
}

echo "<h2 style='color:green'>XML is Well Formed</h2>";

if(!$dom->schemaValidate("student.xsd"))
{
    echo "<h2 style='color:red'>XML does NOT follow XSD</h2>";

    foreach(libxml_get_errors() as $error){
        echo $error->message."<br>";
    }

    exit();
}

echo "<h2 style='color:green'>XSD Validation Successful</h2>";

$xml = simplexml_load_string($xmlString);

$name = (string)$xml->Name;
$roll = (int)$xml->RollNumber;

$conn->query("INSERT INTO students(student_name,roll_number)
VALUES('$name','$roll')");

$student_id = $conn->insert_id;

foreach($xml->Subjects->Subject as $subject)
{

    $subjectName = (string)$subject->Name;
    $marks = (int)$subject->Marks;

    $conn->query("INSERT INTO subject_marks(student_id,subject_name,marks)
    VALUES($student_id,'$subjectName',$marks)");
}

echo "<h2>Student Uploaded Successfully</h2>";

echo "<a href='index.php'>Back</a>";

?>