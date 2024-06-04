import numpy as np
from influxdb import InfluxDBClient
import ruptures as rpt

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

# Fonction pour effectuer l'analyse de rupture sur une série temporelle
def analyze_ruptures(data):
    algo = rpt.Pelt(model="rbf").fit(data)
    result = algo.predict(pen=10)  # Ajustez le paramètre 'pen' selon vos besoins
    return result

# Fonction pour insérer les points de rupture dans InfluxDB
def insert_ruptures_to_influxdb(time_data, rupture_points, measurement_name):
    points = [
        {
            "measurement": measurement_name,
            "time": time_data[point - 1],  # Utiliser l'index du point de rupture
            "fields": {
                "rupture": 1
            }
        }
        for point in rupture_points
    ]
    client.write_points(points)

# Récupérer les données
data = fetch_data()

# Analyser les ruptures pour chaque série temporelle
rupture_points_humidity = analyze_ruptures(data['humidity'])
rupture_points_light = analyze_ruptures(data['light'])
rupture_points_moisture = analyze_ruptures(data['moisture'])
rupture_points_temperature = analyze_ruptures(data['temperature'])

# Insérer les points de rupture dans InfluxDB
insert_ruptures_to_influxdb(data['time'], rupture_points_humidity, "humidity_ruptures")
insert_ruptures_to_influxdb(data['time'], rupture_points_light, "light_ruptures")
insert_ruptures_to_influxdb(data['time'], rupture_points_moisture, "moisture_ruptures")
insert_ruptures_to_influxdb(data['time'], rupture_points_temperature, "temperature_ruptures")

print("Rupture data has been written to InfluxDB.")
