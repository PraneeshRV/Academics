USE studentdb;
DROP TABLE IF EXISTS marks;

CREATE TABLE marks (
    id          INT AUTO_INCREMENT PRIMARY KEY,
    name        VARCHAR(255) NOT NULL,
    roll_number VARCHAR(100) NOT NULL,
    sub1_name   VARCHAR(100), sub1_mark INT,
    sub2_name   VARCHAR(100), sub2_mark INT,
    sub3_name   VARCHAR(100), sub3_mark INT,
    sub4_name   VARCHAR(100), sub4_mark INT,
    sub5_name   VARCHAR(100), sub5_mark INT,
    created_at  TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);