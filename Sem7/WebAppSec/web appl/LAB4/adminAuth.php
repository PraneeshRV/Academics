<?php

include "auth.php";

if($_SESSION['role']!="admin")
{
    http_response_code(403);

    die("403 Forbidden <br><br> Admin Access Only.");
}

?>