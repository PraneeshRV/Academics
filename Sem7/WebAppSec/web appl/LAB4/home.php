<?php
include "auth.php";
include "db.php";
?>

<!DOCTYPE html>
<html>

<head>
    <title>Home</title>
</head>

<body>

<h2>Welcome <?php echo $_SESSION['username']; ?></h2>

<p>Role: <b><?php echo $_SESSION['role']; ?></b></p>

<a href="profile.php">Update Profile</a> |
<a href="logout.php">Logout</a>

<?php
if($_SESSION['role']=="admin")
{
    echo " | <a href='admin.php'>Admin Panel</a>";
}
?>

<hr>

<h3>Products</h3>

<table border="1" cellpadding="8">

<tr>

<th>ID</th>
<th>Name</th>
<th>Price</th>

</tr>

<?php

$result = $conn->query("SELECT * FROM products");

while($row=$result->fetch_assoc())
{

echo "<tr>";

echo "<td>".$row['id']."</td>";

echo "<td>".$row['name']."</td>";

echo "<td>".$row['price']."</td>";

echo "</tr>";

}

?>

</table>

</body>
</html>