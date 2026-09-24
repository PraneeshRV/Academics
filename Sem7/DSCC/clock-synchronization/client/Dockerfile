FROM python:3.12-alpine

ENV PYTHONUNBUFFERED=1 \
    PYTHONDONTWRITEBYTECODE=1 \
    CLIENT_ID=client \
    MASTER_HOST=clock-master \
    MASTER_PORT=5000 \
    CLOCK_OFFSET=0

RUN adduser -D -H -u 10001 clock

WORKDIR /app

COPY client.py .

USER clock

CMD ["python", "client.py"]
