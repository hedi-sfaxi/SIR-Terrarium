import logging
from dto import TaskManager
from influxdb import InfluxDBClient
from utils import fetch_sensors_data, insert_correlation_to_influxdb, calculate_correlation, insert_ruptures_to_influxdb, analyze_ruptures

def correlation(client : InfluxDBClient, param1: str, param2: str, task_id: str, taskManager: TaskManager):
    try:
        data = fetch_sensors_data(client, [param1, param2])
        correlation_data = calculate_correlation(data[param1], data[param2])
        insert_correlation_to_influxdb(client, data['time'], correlation_data, f"{param1}_{param2}_correlation") #TODO: manage measurement name

        logging.info("Correlation data has been written to InfluxDB.")
        taskManager.update_task_status(task_id, "SUCCESS")
    except:
        logging.error("An error occured during correlation analysis.")
        taskManager.update_task_status(task_id, "FAILED")

def ruptures(client : InfluxDBClient, params: list, task_id: str, taskManager: TaskManager):
    try:
        data = fetch_sensors_data(client, params)
        for param in params:
            rupture_points = analyze_ruptures(data[param])
            insert_ruptures_to_influxdb(client, data['time'], rupture_points, f"{param}_ruptures")

        logging.info("Rupture data has been written to InfluxDB.")
        taskManager.update_task_status(task_id, "SUCCESS")
    except:
        logging.error("An error occured during rupture analysis.")
        taskManager.update_task_status(task_id, "FAILED")