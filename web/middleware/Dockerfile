FROM python:3.11.2-slim

WORKDIR /app

COPY requirements.txt requirements.txt

RUN python3 -m venv venv && \
    . venv/bin/activate && \
    pip install --no-cache-dir -r requirements.txt

RUN pip install -r requirements.txt

CMD ["python3", "main.py"]