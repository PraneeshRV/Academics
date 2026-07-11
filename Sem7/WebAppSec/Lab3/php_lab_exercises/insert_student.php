<?php

$conn = mysqli_connect("localhost", "root", "yourpassword", "php_lab");
if(!$conn)
{
    die("Connection failed: " . mysqli_connect_error());
}

if($_SERVER["REQUEST_METHOD"] == "POST")
{
    $name = trim($_POST["name"]);
    $email = trim($_POST["email"]);
    $age = (int)$_POST["age"];

    // Prepared statement helps safely insert data into the database
    $stmt = mysqli_prepare($conn, "INSERT INTO students (name, email, age) VALUES (?, ?, ?)");
    mysqli_stmt_bind_param($stmt, "ssi", $name, $email, $age);
    mysqli_stmt_execute($stmt);

    echo "<p style='color:green;'>Student record inserted successfully.</p>";

    mysqli_stmt_close($stmt);
}

// Fetch all student records from the database
$result = mysqli_query($conn, "SELECT * FROM students");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Student Records</title>
</head>
<body>

<h2>Insert Student Record</h2>

<form method="post">
    Name:
    <input type="text" name="name">
    <br><br>

    Email:
    <input type="email" name="email">
    <br><br>

    Age:
    <input type="number" name="age">
    <br><br>

    <input type="submit" value="Save">
</form>

<h2>Student List</h2>

<table border="1" cellpadding="8">
    <tr>
        <th>ID</th>
        <th>Name</th>
        <th>Email</th>
        <th>Age</th>
    </tr>

    <?php
    while($row = mysqli_fetch_assoc($result))
    {
        echo "<tr>";
        echo "<td>".$row["id"]."</td>";
        echo "<td>".$row["name"]."</td>";
        echo "<td>".$row["email"]."</td>";
        echo "<td>".$row["age"]."</td>";
        echo "</tr>";
    }
    ?>
</table>

</body>
</html>
