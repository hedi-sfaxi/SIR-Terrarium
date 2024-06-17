from influxdb import InfluxDBClient
import numpy as np
import ruptures as rpt

"""
Fetch sensors data from InfluxDB
"""
def fetch_sensors_data(client : InfluxDBClient, params: list):
    client.switch_database('sensor_data')
    params_str = ', '.join([f'"{param}"' for param in params])
    query = f'SELECT {params_str} FROM sensor_data'
    results = client.query(query)
    points = list(results.get_points())

    sortie = {param : np.array([point[param] for point in points], dtype=float) for param in params}
    sortie['time'] = [point['time'] for point in points]

    return sortie

"""
Insert the correlation data to InfluxDB
"""
def insert_correlation_to_influxdb(client : InfluxDBClient, time_data, correlation_data, measurement_name):
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

"""
Calculate the correlation between two time series
"""
def calculate_correlation(series1, series2):
    correlation = np.correlate(series1 - np.mean(series1), series2 - np.mean(series2), mode='same') / (np.std(series1) * np.std(series2) * len(series1))
    return correlation

"""
Analyze ruptures on a time series
"""
def analyze_ruptures(data):
    algo = rpt.Pelt(model="rbf").fit(data)
    result = algo.predict(pen=10)  # Ajustez le paramètre 'pen' selon vos besoins
    return result

"""
Insert rupture points to InfluxDB
"""
def insert_ruptures_to_influxdb(client : InfluxDBClient, time_data, rupture_points, measurement_name):
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


"""
Task statuses
"""
task_statuses = {}

"""
Initialize the task statuses
"""
def init_task_status():
    task_statuses.clear()

"""
Get the status of a task
"""
def get_task_status(taskId):
    return task_statuses.get(taskId, None)

"""
Update the status of a task
"""
def update_task_status(taskId, status):
    task_statuses[taskId] = status