DROP DATABASE IF EXISTS dbtest;
CREATE DATABASE dbtest;
USE dbtest;

CREATE TABLE employee (
  ID       INT(6)      NOT NULL AUTO_INCREMENT,
  Name     VARCHAR(30) NOT NULL,
  EID      VARCHAR(7)  NOT NULL,
  Password VARCHAR(60),
  Salary   INT(10),
  SSN      VARCHAR(11),
  PRIMARY KEY (ID)
);

INSERT INTO employee (Name, EID, Password, Salary, SSN) VALUES
 ('Alice',   'EID5000', 'paswd123', 80000, '555-55-5555'),
 ('Bob',     'EID5001', 'paswd123', 80000, '555-66-5555'),
 ('Charlie', 'EID5002', 'paswd123', 80000, '555-77-5555'),
 ('David',   'EID5003', 'paswd123', 80000, '555-88-5555');
