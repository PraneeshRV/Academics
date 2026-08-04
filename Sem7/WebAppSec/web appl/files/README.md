# Student Marks Portal (XML → validate → MySQL → grade)

## Files
- `student.xml`   – your data: email + 5 subject marks
- `student.xsd`   – schema used to validate the XML
- `setup.sql`     – creates the database + table
- `db.php`        – MySQL connection
- `upload.php`    – validates XML, inserts into DB
- `calculate.php` – reads DB, computes grade
- `index.php`     – the two buttons

## Setup (XAMPP)

1. Start **Apache** and **MySQL** from the XAMPP Control Panel.

2. Copy this whole `marks_portal` folder into:
   `C:\xampp\htdocs\marks_portal`

3. Create the database: open `http://localhost/phpmyadmin` →
   Import tab → choose `setup.sql` → Go.
   (Or paste its contents into the SQL tab.)

4. Open the app: `http://localhost/marks_portal/index.php`

## How it flows
XML file  →  upload.php checks well-formedness + XSD  →  if valid, inserts row into `marks`
Button "Calculate Grade"  →  calculate.php SELECTs the row by email  →  averages the 5 marks  →  returns grade.

## Grade cut-offs (edit in calculate.php)
>=90 A+ | >=80 A | >=70 B | >=60 C | >=50 D | else F

## Notes
- Change the email / marks by editing `student.xml`, then click Upload again.
- `db.php` assumes XAMPP defaults (user `root`, no password). Change if yours differ.
