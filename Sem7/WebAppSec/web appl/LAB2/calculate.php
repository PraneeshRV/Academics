<?php

include("db.php");

$result=$conn->query("SELECT students.student_name,
students.roll_number,
subject_marks.*

FROM students

JOIN subject_marks

ON students.id=subject_marks.student_id");

echo "<h2>Student Grades</h2>";

echo "<table>";

echo "<tr>

<th>Name</th>

<th>Roll</th>

<th>Subject</th>

<th>Marks</th>

<th>Grade</th>

</tr>";

$total=0;

$count=0;

while($row=$result->fetch_assoc())
{

$marks=$row['marks'];

if($marks>=90)
$grade="A+";

else if($marks>=80)
$grade="A";

else if($marks>=70)
$grade="B+";

else if($marks>=60)
$grade="B";

else if($marks>=50)
$grade="C";

else if($marks>=40)
$grade="D";

else
$grade="F";

$conn->query("UPDATE subject_marks
SET grade='$grade'
WHERE id=".$row['id']);

echo "<tr>";

echo "<td>".$row['student_name']."</td>";

echo "<td>".$row['roll_number']."</td>";

echo "<td>".$row['subject_name']."</td>";

echo "<td>".$marks."</td>";

echo "<td>".$grade."</td>";

echo "</tr>";

$total+=$marks;

$count++;

}

echo "</table>";

$avg=$total/$count;

echo "<h3>Average Marks : ".number_format($avg,2)."</h3>";

if($avg>=90)
$overall="A+";
else if($avg>=80)
$overall="A";
else if($avg>=70)
$overall="B+";
else if($avg>=60)
$overall="B";
else if($avg>=50)
$overall="C";
else if($avg>=40)
$overall="D";
else
$overall="F";

echo "<h2>Overall Grade : $overall</h2>";

?>