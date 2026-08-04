CREATE DATABASE studentxml;

USE studentxml;

CREATE TABLE students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    roll_number INT UNIQUE,
    student_name VARCHAR(100)
);

CREATE TABLE subject_marks (
    id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT,
    subject_name VARCHAR(100),
    marks INT,
    grade VARCHAR(5),
    FOREIGN KEY(student_id) REFERENCES students(id)
);