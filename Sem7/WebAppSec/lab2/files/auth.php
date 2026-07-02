<?php
/**
 * auth.php — include at the top of any page that requires a signed-in user.
 *
 *   require __DIR__ . '/auth.php';
 *   // $currentUserId and $currentUserEmail are now available
 */

declare(strict_types=1);
session_start();

if (empty($_SESSION['user_id'])) {
    header('Location: /login.html');
    exit;
}

$currentUserId    = $_SESSION['user_id'];
$currentUserEmail = $_SESSION['email'] ?? null;
