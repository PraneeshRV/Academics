<?php
// Database connection configuration for LAMPP MySQL
$db_host = 'localhost';
$db_user = 'root';
$db_pass = '';
$db_name = 'sqli_lab';
$socket  = '/opt/lampp/var/mysql/mysql.sock';

// Suppress default warning to handle error gracefully
mysqli_report(MYSQLI_REPORT_OFF);

// Attempt standard connection first
$conn = @mysqli_connect($db_host, $db_user, $db_pass, $db_name);

// Fallback to explicit LAMPP socket if running under system PHP
if (!$conn && file_exists($socket)) {
    $conn = @mysqli_connect($db_host, $db_user, $db_pass, $db_name, 3306, $socket);
}

if (!$conn) {
    die("<div style='color:#f87171; font-weight:bold; font-family:sans-serif; padding:20px; border:1px solid #ef4444; background:#1e1b4b; border-radius:8px; margin:20px;'>
        <h3>❌ Database Connection Failed</h3>
        <p style='margin-top:8px;'>Error details: " . htmlspecialchars(mysqli_connect_error()) . "</p>
        <p style='margin-top:8px; font-weight:normal; color:#cbd5e1;'>Please make sure LAMPP MySQL service is running:</p>
        <code style='background:#0f172a; padding:6px 12px; border-radius:4px; display:inline-block; margin-top:6px; color:#38bdf8;'>sudo /opt/lampp/lampp startmysql</code>
    </div>");
}
?>
