<?php

require 'db.php';

$mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'vuln';
$eid  = isset($_REQUEST['EID']) ? $_REQUEST['EID'] : '';
$pwd  = isset($_REQUEST['Password']) ? $_REQUEST['Password'] : '';
$conn = getDB();

echo "[mode=$mode] EID=<$eid> Password=<$pwd>\n";

if ($mode === 'prepared') {
    
    $sql = "SELECT ID, Name, EID, Salary, SSN FROM employee WHERE EID = ? AND Password = ?";
    if ($stmt = $conn->prepare($sql)) {
        $stmt->bind_param("ss", $eid, $pwd);          
        $stmt->execute();
        $stmt->bind_result($id, $name, $e, $salary, $ssn);
        $rows = 0;
        while ($stmt->fetch()) {
            printf("  ID:%s  Name:%s  EID:%s  Salary:%s  SSN:%s\n", $id, $name, $e, $salary, $ssn);
            $rows++;
        }
        echo "  -> rows returned: $rows\n";
        $stmt->close();
    }
} else {
    if ($mode === 'escape') {
        
        $eid = $conn->real_escape_string($eid);
        $pwd = $conn->real_escape_string($pwd);
    }
    
    $sql = "SELECT ID, Name, EID, Salary, SSN FROM employee WHERE EID = '$eid' AND Password = '$pwd'";
    echo "  SQL: $sql\n";
    $result = $conn->query($sql);
    if ($result) {
        $rows = 0;
        while ($row = $result->fetch_assoc()) {
            printf("  ID:%s  Name:%s  EID:%s  Salary:%s  SSN:%s\n",
                   $row['ID'], $row['Name'], $row['EID'], $row['Salary'], $row['SSN']);
            $rows++;
        }
        echo "  -> rows returned: $rows\n";
        $result->free();
    } else {
        echo "  QUERY ERROR (" . $conn->errno . "): " . $conn->error . "\n";
    }
}
$conn->close();
?>
