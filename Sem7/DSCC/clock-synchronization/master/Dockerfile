FROM python:3.12-alpine

WORKDIR /app
ENV PYTHONUNBUFFERED=1

COPY master.py .

EXPOSE 5000
CMD ["python", "master.py"]
