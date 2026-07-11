<?php
session_start();

if(isset($_POST["login"]))
{
    $username = $_POST["username"];
    $password = $_POST["password"];

    // Simple hardcoded login check for learning purposes
    if($username === "admin" && $password === "1234")
    {
        $_SESSION["username"] = $username;
        header("Location: dashboard.php");
        exit();
    }
    else
    {
        $error = "Invalid username or password";
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>

<h2>Login Form</h2>

<?php
if(isset($error))
{
    echo "<p style='color:red;'>$error</p>";
}
?>

<form method="post">
    Username:
    <input type="text" name="username">
    <br><br>

    Password:
    <input type="password" name="password">
    <br><br>

    <input type="submit" name="login" value="Login">
</form>

</body>
</html>
