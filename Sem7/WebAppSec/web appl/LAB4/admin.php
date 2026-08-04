<?php
include "adminAuth.php";
include "db.php";
?>

<!DOCTYPE html>
<html>

<head>

<title>Admin Panel</title>

<style>

body{
    font-family: Arial;
    margin:40px;
}

table{
    border-collapse: collapse;
    width:70%;
}

th,td{
    border:1px solid black;
    padding:10px;
    text-align:center;
}

button{
    padding:8px 15px;
    cursor:pointer;
}

input{
    padding:8px;
    width:250px;
}

a{
    text-decoration:none;
}

</style>

</head>


<body>


<h2>Admin Panel</h2>

<p>
Welcome:
<?php echo $_SESSION['username']; ?>
</p>


<a href="home.php">Home</a> |
<a href="logout.php">Logout</a>


<hr>


<h3>Add Product</h3>


<form action="addProduct.php" method="POST">


Product Name

<br>

<input 
type="text" 
name="name"
required>


<br><br>


Price

<br>

<input 
type="number"
name="price"
required>


<br><br>


<input 
type="submit"
value="Add Product">


</form>


<hr>


<h3>Product Database</h3>


<button onclick="loadProducts()">
Show Products
</button>


<br><br>


<div id="result"></div>



<script>


function loadProducts(){


fetch("getProducts.php")


.then(response=>response.json())


.then(data=>{


let html = "<table>";


html += "<tr>";

html += "<th>ID</th>";
html += "<th>Name</th>";
html += "<th>Price</th>";
html += "<th>Update</th>";
html += "<th>Delete</th>";

html += "</tr>";



data.forEach(function(product){


html += "<tr>";


html += "<td>"+product.id+"</td>";

html += "<td>"+product.name+"</td>";

html += "<td>"+product.price+"</td>";



html += 
"<td><a href='editProduct.php?id="+product.id+"'>Update</a></td>";



html += 
"<td><a href='deleteProduct.php?id="+product.id+"' onclick='return confirm(\"Delete this product?\")'>Delete</a></td>";



html += "</tr>";



});



html += "</table>";



document.getElementById("result").innerHTML=html;



})


.catch(error=>{

document.getElementById("result").innerHTML=
"Error loading products";

});


}



</script>



</body>

</html>