<?php

include "adminAuth.php";
include "db.php";


$id=$_GET['id'];


$stmt=$conn->prepare("SELECT * FROM products WHERE id=?");

$stmt->bind_param("i",$id);

$stmt->execute();

$result=$stmt->get_result();

$product=$result->fetch_assoc();


?>


<!DOCTYPE html>
<html>

<head>

<title>Edit Product</title>

</head>


<body>


<h2>Edit Product</h2>


<form action="updateProduct.php" method="POST">


<input 
type="hidden"
name="id"
value="<?php echo $product['id']; ?>">


Product Name

<br>

<input
type="text"
name="name"
value="<?php echo $product['name']; ?>"
required>


<br><br>


Price

<br>

<input
type="number"
name="price"
value="<?php echo $product['price']; ?>"
required>


<br><br>


<input
type="submit"
value="Update Product">


</form>


<br>

<a href="admin.php">
Back
</a>


</body>

</html>