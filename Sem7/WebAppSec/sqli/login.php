<?php

require 'db.php';

$mode   = isset($_POST['mode']) ? $_POST['mode'] : 'vuln';
$eid    = isset($_POST['EID']) ? $_POST['EID'] : '';
$pwd    = isset($_POST['Password']) ? $_POST['Password'] : '';
$did_submit = ($_SERVER['REQUEST_METHOD'] === 'POST');

$user = null;       
$all  = array();    
$debug_sql = '';
$err = '';

if ($did_submit) {
    $conn = getDB();
    if ($mode === 'prepared') {
        $sql = "SELECT ID, Name, EID, Salary, SSN FROM employee WHERE EID = ? AND Password = ?";
        if ($stmt = $conn->prepare($sql)) {
            $stmt->bind_param("ss", $eid, $pwd);
            $stmt->execute();
            $stmt->bind_result($id,$name,$e,$salary,$ssn);
            while ($stmt->fetch()) { $all[] = array($id,$name,$e,$salary,$ssn); }
            $stmt->close();
        }
        $debug_sql = "PREPARED: SELECT ... WHERE EID=? AND Password=?  [bound: EID='{$eid}', Password='{$pwd}']";
    } else {
        $ein = $eid; $pin = $pwd;
        if ($mode === 'escape') { $ein = $conn->real_escape_string($eid); $pin = $conn->real_escape_string($pwd); }
        $sql = "SELECT ID, Name, EID, Salary, SSN FROM employee WHERE EID = '$ein' AND Password = '$pin'";
        $debug_sql = $sql;
        if ($res = $conn->query($sql)) {
            while ($row = $res->fetch_assoc()) {
                $all[] = array($row['ID'],$row['Name'],$row['EID'],$row['Salary'],$row['SSN']);
            }
            $res->free();
        } else {
            $err = "SQL error (".$conn->errno."): ".$conn->error;
        }
    }
    $conn->close();
    if (count($all) > 0) { $user = $all[0]; }
}
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Employee Portal — Login</title>
<style>
  body{font-family:'Segoe UI',Arial,sans-serif;background:#eef2f7;margin:0}
  .card{background:#fff;max-width:360px;margin:70px auto;padding:32px 34px;
        border-radius:10px;box-shadow:0 8px 30px rgba(0,0,0,.12)}
  h1{font-size:20px;margin:0 0 4px;color:#1f3b63;text-align:center}
  p.sub{margin:0 0 22px;color:#7a8aa0;font-size:13px;text-align:center}
  label{display:block;font-size:13px;color:#42506b;margin:12px 0 5px}
  input[type=text],input[type=password],select{width:100%;box-sizing:border-box;
        padding:10px;border:1px solid #cbd5e1;border-radius:6px;font-size:14px}
  button{width:100%;margin-top:20px;padding:11px;background:#2563eb;color:#fff;
        border:0;border-radius:6px;font-size:15px;cursor:pointer}
  button:hover{background:#1d4ed8}
  .mode{margin-top:18px;padding-top:14px;border-top:1px dashed #e2e8f0}
  .ok{background:#e7f7ed;border:1px solid #86efac;color:#166534}
  .bad{background:#fdecea;border:1px solid #f5b5ae;color:#8a1c13}
  .box{max-width:560px;margin:22px auto;padding:14px 18px;border-radius:8px;font-size:14px}
  table{border-collapse:collapse;width:100%;margin-top:8px;font-size:13px}
  th,td{border:1px solid #d7deea;padding:6px 8px;text-align:left}
  th{background:#f1f5fb}
  code.sql{display:block;background:#0f172a;color:#93c5fd;padding:10px 12px;border-radius:6px;
        font-size:12px;white-space:pre-wrap;word-break:break-all;max-width:560px;margin:10px auto 0}
</style>
</head>
<body>

<?php if ($did_submit): ?>
  <?php if ($user): ?>
    <div class="box ok">
      ✅ <b>Login successful.</b> Welcome, <b><?php echo htmlspecialchars($user[1]); ?></b>
      (EID <?php echo htmlspecialchars($user[2]); ?>).
      <?php if (count($all) > 1): ?>
        <br>The query returned <b><?php echo count($all); ?></b> records — you pulled more than your own row:
        <table>
          <tr><th>ID</th><th>Name</th><th>EID</th><th>Salary</th><th>SSN</th></tr>
          <?php foreach ($all as $r): ?>
          <tr><?php foreach ($r as $c) echo "<td>".htmlspecialchars($c)."</td>"; ?></tr>
          <?php endforeach; ?>
        </table>
      <?php else: ?>
        <table>
          <tr><th>ID</th><th>Name</th><th>EID</th><th>Salary</th><th>SSN</th></tr>
          <tr><?php foreach ($user as $c) echo "<td>".htmlspecialchars($c)."</td>"; ?></tr>
        </table>
      <?php endif; ?>
    </div>
  <?php else: ?>
    <div class="box bad">❌ <b>Login failed.</b> <?php echo $err ? htmlspecialchars($err) : "Invalid EID or password."; ?></div>
  <?php endif; ?>
  <code class="sql">Query executed [mode=<?php echo htmlspecialchars($mode); ?>]:
<?php echo htmlspecialchars($debug_sql); ?></code>
<?php endif; ?>

<div class="card">
  <h1>Employee Portal</h1>
  <p class="sub">Sign in with your Employee ID</p>
  <form method="post" action="login.php">
    <label>Employee ID</label>
    <input type="text" name="EID" value="<?php echo htmlspecialchars($eid); ?>" autofocus>
    <label>Password</label>
    <input type="password" name="Password" value="">
    <div class="mode">
      <label>Protection mode (for the fix test)</label>
      <select name="mode">
        <option value="vuln"     <?php if($mode==='vuln')echo 'selected';?>>Vulnerable (no protection)</option>
        <option value="escape"   <?php if($mode==='escape')echo 'selected';?>>Fix 1 — real_escape_string</option>
        <option value="prepared" <?php if($mode==='prepared')echo 'selected';?>>Fix 2 — prepared statement</option>
      </select>
    </div>
    <button type="submit">Sign in</button>
  </form>
</div>

</body>
</html>