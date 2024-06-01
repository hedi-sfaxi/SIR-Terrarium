import numpy as np
from influxdb import InfluxDBClient
import pandas as pd

# Connexion à InfluxDB
client = InfluxDBClient(host='192.168.0.2', port=8086)
client.switch_database('sensor_data')

# Fonction pour récupérer les données des capteurs
def fetch_data():
    query = 'SELECT "humidity", "light", "moisture", "temperature" FROM sensor_data'
    results = client.query(query)
    points = list(results.get_points())
    
    humidity_data = [point['humidity'] for point in points]
    light_data = [point['light'] for point in points]
    moisture_data = [point['moisture'] for point in points]
    temperature_data = [point['temperature'] for point in points]
    time_data = [point['time'] for point in points]

    return {
        'time': time_data,
        'humidity': np.array(humidity_data),
        'light': np.array(light_data),
        'moisture': np.array(moisture_data),
        'temperature': np.array(temperature_data)
    }

# Fonction pour calculer la corrélation entre deux séries temporelles
def calculate_correlation(series1, series2):
    correlation = np.correlate(series1 - np.mean(series1), series2 - np.mean(series2), mode='same') / (np.std(series1) * np.std(series2) * len(series1))
    return correlation

# Fonction pour insérer la nouvelle série temporelle dans InfluxDB
def insert_correlation_to_influxdb(time_data, correlation_data, measurement_name):
    points = [
        {
            "measurement": measurement_name,
            "time": time_data[i],
            "fields": {
                "correlation": correlation_data[i]
            }
        }
        for i in range(len(time_data))
    ]
    client.write_points(points)

# Récupérer les données
data = fetch_data()

# Calculer la corrélation entre 'light' et 'humidity'
correlation_data = calculate_correlation(data['light'], data['humidity'])

# Insérer la série temporelle de corrélation dans InfluxDB
insert_correlation_to_influxdb(data['time'], correlation_data, "light_humidity_correlation")

print("Correlation data has been written to InfluxDB.")
