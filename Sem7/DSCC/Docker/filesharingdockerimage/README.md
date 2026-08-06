# 20CYS402 - Distributed Systems and Cloud Computing
## Lab #2 - Internal File Sharing Service

**Student:** Praneesh R V
**Roll Number:** 36
**DockerHub:** shadoweternity

### Description
A lightweight internal file-sharing service built with Python Flask, containerized
with Docker for consistent deployment across environments.

### Features
- Upload files through the web UI
- List and download shared files
- Configuration via `config.json` and environment variables
- Health check endpoint at `/health`

### Environment Variables
| Variable      | Description                        | Default          |
|---------------|-------------------------------------|------------------|
| `APP_ENV`     | Deployment environment              | `production`     |
| `APP_PORT`    | Port the Flask app listens on       | `8000`           |
| `UPLOAD_DIR`  | Directory where files are stored    | `/app/uploads`   |

### Run Locally (without Docker)
```
pip install -r requirements.txt
python server.py
```

### Run with Docker
```
docker build -t filesharingdockerimage:latest .
docker run -d -p 8036:8000 --name filesharing_container filesharingdockerimage:latest
```

Then open: http://localhost:8036
