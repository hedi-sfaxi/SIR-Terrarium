FROM python:3.11.2-slim

WORKDIR /app

COPY app/ /app

COPY requirements.txt requirements.txt

RUN pip install --no-cache-dir -r requirements.txt

EXPOSE 8082

CMD ["python3", "main.py"]