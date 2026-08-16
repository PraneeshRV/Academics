FROM alpine:latest

ENV ROLLNUMBER="CB.SC.U4CYS23036"
ENV NAME="Praneesh R V"

LABEL EMAIL="praneeshrv404@gmail.com"
LABEL PRODUCTION_VERSION="1.0"

WORKDIR /midterm-exam

RUN apk add --no-cache mariadb mariadb-client python3 py3-pip py3-flask py3-pymysql && \
    sed -i 's/skip-networking/#skip-networking/g' /etc/my.cnf.d/mariadb-server.cnf

COPY database/init.sql /tmp/init.sql

RUN mkdir -p /run/mysqld /var/lib/mysql && \
    chown -R mysql:mysql /run/mysqld /var/lib/mysql && \
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null 2>&1 && \
    mariadbd --user=mysql --datadir=/var/lib/mysql & \
    sleep 3 && \
    mariadb < /tmp/init.sql && \
    mariadb-admin shutdown && \
    rm /tmp/init.sql


COPY . /midterm-exam/

EXPOSE 5000

CMD ["sh", "-c", "mariadbd --user=mysql --datadir=/var/lib/mysql & sleep 2 && python3 web/app.py"]