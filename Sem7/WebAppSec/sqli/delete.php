<?php

require 'db.php';

$mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'vuln';
$eid  = isset($_REQUEST['EID']) ? $_REQUEST['EID'] : '';
$pwd  = isset($_REQUEST['Password']) ? $_REQUEST['Password'] : '';
$conn = getDB();

echo "[mode=$mode] EID=<$eid> Password=<$pwd>\n";

if ($mode === 'prepared') {
    
    $sql = "DELETE FROM employee WHERE EID = ? AND Password = ?";
    if ($stmt = $conn->prepare($sql)) {
        $stmt->bind_param("ss", $eid, $pwd);
        $stmt->execute();
        echo "  -> rows deleted: " . $stmt->affected_rows . "\n";
        $stmt->close();
    }
} else {
    if ($mode === 'escape') {
        
        $eid = $conn->real_escape_string($eid);
        $pwd = $conn->real_escape_string($pwd);
    }
    
    $sql = "DELETE FROM employee WHERE EID = '$eid' AND Password = '$pwd'";
    echo "  SQL: $sql\n";
    if ($conn->query($sql)) {
        echo "  -> rows deleted: " . $conn->affected_rows . "\n";
    } else {
        echo "  DELETE ERROR (" . $conn->errno . "): " . $conn->error . "\n";
    }
}
$conn->close();
?>
