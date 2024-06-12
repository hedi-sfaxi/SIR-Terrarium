FROM python:3.11.2-slim

WORKDIR /app

COPY app/ app/

COPY requirements.txt requirements.txt

RUN ls -l /app

RUN python3 -m venv venv && \
    . venv/bin/activate && \
    pip install --no-cache-dir -r requirements.txt

CMD ["python3", "/app/main.py"]