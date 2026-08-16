CREATE DATABASE IF NOT EXISTS midterm_db;

CREATE USER IF NOT EXISTS 'midterm_user'@'localhost' IDENTIFIED BY 'midterm_pass';
CREATE USER IF NOT EXISTS 'midterm_user'@'%' IDENTIFIED BY 'midterm_pass';
CREATE USER IF NOT EXISTS 'midterm_user'@'127.0.0.1' IDENTIFIED BY 'midterm_pass';

GRANT ALL PRIVILEGES ON midterm_db.* TO 'midterm_user'@'localhost';
GRANT ALL PRIVILEGES ON midterm_db.* TO 'midterm_user'@'%';
GRANT ALL PRIVILEGES ON midterm_db.* TO 'midterm_user'@'127.0.0.1';
FLUSH PRIVILEGES;

USE midterm_db;

CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    full_name VARCHAR(100) NOT NULL,
    role VARCHAR(30) DEFAULT 'Student'
);

INSERT INTO users (username, password, full_name, role) VALUES 
('admin', 'admin123', 'Administrator', 'admin'),
('praneesh', 'midterm2026', 'Praneesh R V', 'student'),
('student', 'password123', 'Student User', 'student')
ON DUPLICATE KEY UPDATE 
    password=VALUES(password),
    full_name=VALUES(full_name),
    role=VALUES(role);
