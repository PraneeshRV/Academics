FROM python:3.12-alpine

ENV PYTHONUNBUFFERED=1 \
    PYTHONDONTWRITEBYTECODE=1 \
    MASTER_PORT=5000 \
    REQUEST_DELAY_MS=0 \
    REPLY_DELAY_MS=0

RUN adduser -D -H -u 10001 clock

WORKDIR /app

COPY master.py .

USER clock

EXPOSE 5000

HEALTHCHECK --interval=5s --timeout=3s --start-period=5s --retries=3 \
    CMD python -c "import os, socket; socket.create_connection(('127.0.0.1', int(os.environ['MASTER_PORT'])), 2).close()"

STOPSIGNAL SIGINT

CMD ["python", "master.py"]
