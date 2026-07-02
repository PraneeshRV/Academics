<?php
/**
 * logout.php — destroys the session and clears the cookie.
 */

declare(strict_types=1);
session_start();

$_SESSION = [];

if (ini_get('session.use_cookies')) {
    $params = session_get_cookie_params();
    setcookie(session_name(), '', time() - 42000,
        $params['path'], $params['domain'],
        $params['secure'], $params['httponly']
    );
}

session_destroy();
header('Location: /login.html');
exit;
