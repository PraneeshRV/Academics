<!DOCTYPE html>
<html>

<head>

<title>Student XML Upload</title>

<link rel="stylesheet" href="style.css">

</head>

<body>

<div class="container">

<h2>Student XML Upload System</h2>

<form action="upload.php" method="post">

<textarea name="xml" rows="20" cols="80"
placeholder="Paste XML Here"></textarea>

<br><br>

<input type="submit" value="Validate & Upload">

</form>

<br>

<form action="calculate.php">

<input type="submit" value="Calculate Grades">

</form>

</div>

</body>

</html>