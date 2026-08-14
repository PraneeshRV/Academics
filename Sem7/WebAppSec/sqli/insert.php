<?php

require 'db.php';

$mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'vuln';
$name = isset($_REQUEST['Name']) ? $_REQUEST['Name'] : '';
$eid  = isset($_REQUEST['EID']) ? $_REQUEST['EID'] : '';
$pwd  = isset($_REQUEST['Password']) ? $_REQUEST['Password'] : '';
$conn = getDB();

echo "[mode=$mode] Name=<$name> EID=<$eid> Password=<$pwd>  (app intends Salary=50000, SSN=000-00-0000)\n";

if ($mode === 'prepared') {
    
    $salary = 50000; $ssn = '000-00-0000';
    $sql = "INSERT INTO employee (Name, EID, Password, Salary, SSN) VALUES (?, ?, ?, ?, ?)";
    if ($stmt = $conn->prepare($sql)) {
        $stmt->bind_param("sssis", $name, $eid, $pwd, $salary, $ssn);
        $ok = $stmt->execute();
        echo $ok ? "  -> inserted 1 row (id " . $conn->insert_id . ")\n"
                 : "  INSERT ERROR (" . $stmt->errno . "): " . $stmt->error . "\n";
        $stmt->close();
    }
} else {
    if ($mode === 'escape') {
        
        $name = $conn->real_escape_string($name);
        $eid  = $conn->real_escape_string($eid);
        $pwd  = $conn->real_escape_string($pwd);
    }
    
    $sql = "INSERT INTO employee (Name, EID, Password, Salary, SSN) VALUES ('$name', '$eid', '$pwd', 50000, '000-00-0000')";
    echo "  SQL: $sql\n";
    if ($conn->query($sql)) {
        echo "  -> inserted 1 row (id " . $conn->insert_id . ")\n";
    } else {
        echo "  INSERT ERROR (" . $conn->errno . "): " . $conn->error . "\n";
    }
}
$conn->close();
?>
