# Base Image
FROM python:3.12-slim

# Maintainer
LABEL maintainer="Praneesh R V"
LABEL email="praneeshrv404@gmail.com"

# Install system packages required by the application
RUN apt-get update && \
    apt-get install -y curl && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
# Environment Variables
ENV APP_ENV=production
ENV APP_PORT=8000
ENV UPLOAD_DIR=/app/uploads

# Working Directory
WORKDIR /app

# Copy application files and directories
COPY server.py .
COPY requirements.txt .
COPY config.json .
COPY README.md .z
COPY uploads/ ./uploads/

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Expose application port
EXPOSE 8000

# Start the application automatically when the container runs
CMD ["python", "server.py"]
