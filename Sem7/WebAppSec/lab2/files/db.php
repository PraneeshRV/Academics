<?php
/**
 * db.php — single PDO connection, reused by every script.
 * Keep real credentials out of source control: load from environment
 * variables in production rather than hardcoding them here.
 */

$DB_HOST = getenv('DB_HOST') ?: '127.0.0.1';
$DB_NAME = getenv('DB_NAME') ?: 'atelier';
$DB_USER = getenv('DB_USER') ?: 'atelier_app';
$DB_PASS = getenv('DB_PASS') ?: '';

try {
    $pdo = new PDO(
        "mysql:host={$DB_HOST};dbname={$DB_NAME};charset=utf8mb4",
        $DB_USER,
        $DB_PASS,
        [
            PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES   => false,
        ]
    );
} catch (PDOException $e) {
    // Never leak DB internals to the client.
    error_log('DB connection failed: ' . $e->getMessage());
    http_response_code(500);
    die('Service unavailable. Please try again shortly.');
}
