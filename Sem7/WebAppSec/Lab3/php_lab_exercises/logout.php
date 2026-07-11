<?php
session_start();

// Remove all session variables
session_unset();

// Destroy the session completely
session_destroy();

header("Location: login.php");
exit();
?>
