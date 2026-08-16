FROM alpine:latest

ENV ROLLNUMBER="CB.SC.U4CYS23036"
ENV NAME="Praneesh R V"

LABEL EMAIL="praneeshrv404@gmail.com"
LABEL "PRODUCTION VERSION"="1.0"
LABEL PRODUCTION_VERSION="1.0"
LABEL description="DSCC Midterm Exam Web Authentication Container"

WORKDIR /midterm-exam

RUN printf "nameserver 1.1.1.1\nnameserver 8.8.8.8\n" > /etc/resolv.conf && \
    apk add --no-cache mariadb mariadb-client python3 py3-pip py3-flask py3-pymysql

RUN mkdir -p /run/mysqld /var/lib/mysql && \
    chown -R mysql:mysql /run/mysqld /var/lib/mysql && \
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null 2>&1 && \
    mariadbd --user=mysql --datadir=/var/lib/mysql & \
    sleep 3 && \
    mariadb -e "CREATE DATABASE midterm_db;" && \
    mariadb -e "CREATE USER 'midterm_user'@'localhost' IDENTIFIED BY 'midterm_pass';" && \
    mariadb -e "CREATE USER 'midterm_user'@'127.0.0.1' IDENTIFIED BY 'midterm_pass';" && \
    mariadb -e "GRANT ALL PRIVILEGES ON midterm_db.* TO 'midterm_user'@'localhost';" && \
    mariadb -e "GRANT ALL PRIVILEGES ON midterm_db.* TO 'midterm_user'@'127.0.0.1';" && \
    mariadb -e "FLUSH PRIVILEGES;" && \
    mariadb midterm_db -e "CREATE TABLE users (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(50), password VARCHAR(50), full_name VARCHAR(50), role VARCHAR(50)); INSERT INTO users VALUES (1, 'admin', 'admin123', 'Administrator', 'admin'), (2, 'praneesh', 'midterm2026', 'Praneesh R V', 'student'), (3, 'student', 'password123', 'Student User', 'student');" && \
    mariadb-admin shutdown

COPY . /midterm-exam/

EXPOSE 5000

CMD ["sh", "-c", "mariadbd --user=mysql --datadir=/var/lib/mysql & sleep 2 && python3 web/app.py"]