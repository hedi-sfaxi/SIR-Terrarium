import numpy as np
from influxdb import InfluxDBClient

# Connexion à InfluxDB
client = InfluxDBClient(host='192.168.0.2', port=8086)
client.switch_database('sensor_data')

# Requête pour récupérer les données des capteurs
query = 'SELECT "humidity", "light", "moisture", "temperature" FROM sensor_data'
results = client.query(query)
points = list(results.get_points())

# Extraire les valeurs de la réponse
humidity_data = [point['humidity'] for point in points]
light_data = [point['light'] for point in points]
moisture_data = [point['moisture'] for point in points]
temperature_data = [point['temperature'] for point in points]

# Convertir en tableaux NumPy
humidity_data = np.array(humidity_data)
light_data = np.array(light_data)
moisture_data = np.array(moisture_data)
temperature_data = np.array(temperature_data)

# Afficher les données
print("Humidity Data:", humidity_data)
print("Light Data:", light_data)
print("Moisture Data:", moisture_data)
print("Temperature Data:", temperature_data)
