# Dockerized Web Authentication Application

**Distributed Systems & Cloud Computing (DSCC) — Midterm Examination**  
**Course Outcome:** CO1 | **Marks:** 20  
**Candidate Name:** Praneesh R V  
**Roll Number:** `CB.SC.U4CYS23036`  
**Email:** `praneeshrv404@gmail.com`  

---

## 1. Project Overview & Architecture

This repository contains a containerized Web Authentication Application adhering strictly to all midterm exam requirements:
- **Base Image**: `alpine:latest`
- **Database**: MariaDB Server inside the container (`midterm_db`, user: `midterm_user`, password: `midterm_pass`)
- **Web Application**: Python 3 + Flask + PyMySQL
- **Container Working Directory**: `/midterm-exam`
- **Image Name**: `mt-webauth`
- **Exposed / Host Port**: `5000:5000`

---

## 2. Directory Structure

```text
CB.SC.U4CYS23036_MIDTERM/
├── Dockerfile
├── docker-compose.yml
├── requirements.txt
├── database/
│   └── init.sql
├── web/
│   ├── app.py
│   ├── login.html
│   └── dashboard.html
└── README.md
```

---

## 3. Major Dockerfile & Docker Compose Instructions

### Dockerfile Instructions Explained
1. `FROM alpine:latest` — Establishes a lightweight, secure Alpine Linux base environment.
2. `ENV ROLLNUMBER="CB.SC.U4CYS23036"` & `ENV NAME="Praneesh R V"` — Sets candidate identification environment variables inside the container.
3. `LABEL EMAIL="..."` & `LABEL "PRODUCTION VERSION"="1.0"` — Embeds maintainer metadata and application version into the Docker image manifest.
4. `WORKDIR /midterm-exam` — Sets the root working directory for all container operations.
5. `RUN apt-get update && apt-get install -y mariadb-server ...` — Installs MariaDB server and Python runtime.
6. `COPY requirements.txt ... && pip3 install ...` — Installs required Python libraries.
7. `EXPOSE 5000` — Declares the network listening port for the Flask web application.
8. `ENTRYPOINT ["/midterm-exam/entrypoint.sh"]` — Configures container startup sequence to launch the database and web server.

### Docker Compose Instructions Explained
1. `services.web.build` — Automatically builds the image using local `./Dockerfile`.
2. `image: mt-webauth:1.0` — Tags the image as `mt-webauth:1.0`.
3. `ports: ["5000:5000"]` — Maps container port `5000` to host port `5000` for browser access.
4. `volumes: ["./web:/midterm-exam/web", "./database:/midterm-exam/database"]` — Mounts local host source directories into the container for live updates.
5. `environment` — Passes database credentials and candidate metadata at runtime.

---

## 4. How to Build, Run, and Verify

### Step 1: Build Docker Image
```bash
docker build -t mt-webauth:1.0 -t mt-webauth:latest .
```

### Step 2: Run with Docker Compose
```bash
docker compose up -d
```

### Step 3: Verify Container is Running
```bash
docker compose ps
```

### Step 4: Access in Host Browser
Open: [http://localhost:5000](http://localhost:5000)

---

## 5. Verification & Demonstration Commands

### Verify Environment Variables Inside Container
```bash
docker exec -it mt-webauth-container env | grep -E 'ROLLNUMBER|NAME'
```
**Output:**
```
ROLLNUMBER=CB.SC.U4CYS23036
NAME=Praneesh R V
```

### Verify Image Labels
```bash
docker inspect --format '{{json .Config.Labels}}' mt-webauth:1.0
```
**Output:**
```json
{"EMAIL":"praneeshrv404@gmail.com","PRODUCTION VERSION":"1.0","PRODUCTION_VERSION":"1.0"}
```

### Test User Credentials in Database (`midterm_db`)
| Username | Password | Role | Description |
| :--- | :--- | :--- | :--- |
| `admin` | `admin123` | Administrator | System Administrator test user |
| `praneesh` | `midterm2026` | Candidate | Student candidate test account |
| `student` | `password123` | Student | Generic student test user |

---

## 6. Pushing to Docker Hub

To push the image to your Docker Hub repository:

```bash
# 1. Log in to Docker Hub
docker login -u <YOUR_DOCKERHUB_USERNAME>

# 2. Tag image with your Docker Hub repository namespace
docker tag mt-webauth:1.0 <YOUR_DOCKERHUB_USERNAME>/mt-webauth:1.0
docker tag mt-webauth:latest <YOUR_DOCKERHUB_USERNAME>/mt-webauth:latest

# 3. Push the image
docker push <YOUR_DOCKERHUB_USERNAME>/mt-webauth:1.0
docker push <YOUR_DOCKERHUB_USERNAME>/mt-webauth:latest
```
