<?php
/**
 * login.php — handles POST from login.html's <form>.
 *
 * Flow:
 *   1. Validate input shape (not empty, looks like an email).
 *   2. Check recent failed attempts for this email + IP (rate limit).
 *   3. Look up user, verify password with password_verify().
 *   4. On success: regenerate session id, store user id in session.
 *   5. On failure: log the attempt, return a generic error.
 *
 * Point login.html's <form action="login.php" method="POST">
 * at this file (the demo page currently intercepts submit in JS —
 * remove that preventDefault()/listener if you wire this in for real).
 */

declare(strict_types=1);
session_start();

require __DIR__ . '/db.php';

header('Content-Type: application/json');

const MAX_ATTEMPTS   = 5;      // failed attempts allowed...
const WINDOW_MINUTES  = 15;    // ...within this window
const LOCKOUT_MESSAGE  = 'Too many attempts. Please wait 15 minutes and try again.';
const GENERIC_FAIL     = 'That email and password don\'t match. Check for a typo and try again.';

function respond(int $status, array $body): never {
    http_response_code($status);
    echo json_encode($body);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    respond(405, ['ok' => false, 'error' => 'Method not allowed.']);
}

$email    = trim((string)($_POST['email'] ?? ''));
$password = (string)($_POST['password'] ?? '');
$remember = isset($_POST['remember']);
$ip       = $_SERVER['REMOTE_ADDR'] ?? 'unknown';

// --- 1. Basic input validation ---
if ($email === '' || $password === '') {
    respond(422, ['ok' => false, 'error' => 'Enter both your email and password.']);
}
if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
    respond(422, ['ok' => false, 'error' => 'Enter a valid email address.']);
}

// --- 2. Rate limiting: count recent failed attempts ---
$stmt = $pdo->prepare(
    'SELECT COUNT(*) AS n FROM login_attempts
     WHERE email = :email AND ip_address = :ip
       AND succeeded = 0
       AND attempted_at > (NOW() - INTERVAL :mins MINUTE)'
);
$stmt->execute([':email' => $email, ':ip' => $ip, ':mins' => WINDOW_MINUTES]);
$recentFailures = (int)$stmt->fetch()['n'];

if ($recentFailures >= MAX_ATTEMPTS) {
    respond(429, ['ok' => false, 'error' => LOCKOUT_MESSAGE]);
}

// --- 3. Look up user + verify password ---
$stmt = $pdo->prepare('SELECT id, email, password_hash FROM users WHERE email = :email LIMIT 1');
$stmt->execute([':email' => $email]);
$user = $stmt->fetch();

$logAttempt = function (bool $succeeded) use ($pdo, $email, $ip): void {
    $stmt = $pdo->prepare(
        'INSERT INTO login_attempts (email, ip_address, succeeded) VALUES (:email, :ip, :succeeded)'
    );
    $stmt->execute([':email' => $email, ':ip' => $ip, ':succeeded' => $succeeded ? 1 : 0]);
};

if (!$user || !password_verify($password, $user['password_hash'])) {
    $logAttempt(false);
    respond(401, ['ok' => false, 'error' => GENERIC_FAIL]);
}

// --- 4. Success: rotate session id, store identity ---
session_regenerate_id(true);
$_SESSION['user_id'] = $user['id'];
$_SESSION['email']   = $user['email'];

$logAttempt(true);

// Optional "keep me signed in" — extend the session cookie lifetime
if ($remember) {
    $params = session_get_cookie_params();
    setcookie(session_name(), session_id(), [
        'expires'  => time() + (30 * 24 * 60 * 60), // 30 days
        'path'     => $params['path'],
        'domain'   => $params['domain'],
        'secure'   => true,
        'httponly' => true,
        'samesite' => 'Lax',
    ]);
}

// Rehash transparently if PHP's default cost factor has changed
if (password_needs_rehash($user['password_hash'], PASSWORD_DEFAULT)) {
    $newHash = password_hash($password, PASSWORD_DEFAULT);
    $pdo->prepare('UPDATE users SET password_hash = :hash WHERE id = :id')
        ->execute([':hash' => $newHash, ':id' => $user['id']]);
}

respond(200, ['ok' => true, 'redirect' => '/dashboard.php']);
