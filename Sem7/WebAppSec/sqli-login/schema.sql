-- Database Setup Script for SQL Injection Lab

CREATE DATABASE IF NOT EXISTS sqli_lab;
USE sqli_lab;

-- Drop table if exists for fresh reset
DROP TABLE IF EXISTS users;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    email VARCHAR(100),
    role VARCHAR(20) DEFAULT 'user',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Seed initial accounts
INSERT INTO users (id, username, password, email, role) VALUES
(1, 'admin', 'admin123', 'admin@webappsec.local', 'admin'),
(2, 'alice', 'alice2026', 'alice@webappsec.local', 'user'),
(3, 'bob', 'secretpass', 'bob@webappsec.local', 'user');
