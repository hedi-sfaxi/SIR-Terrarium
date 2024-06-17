import uvicorn
import uuid
from fastapi import FastAPI, HTTPException, BackgroundTasks
from influxdb import InfluxDBClient
from analysis import correlation, ruptures
from sensor_node import irrigate
from utils import update_task_status, get_task_status, init_task_status

app = FastAPI()
influxDbClient = InfluxDBClient(host='influxdb', port=8086)
AUTHORIZED_COLUMNS = ['temperature', 'humidity', 'light', 'moisture', 'pH']
init_task_status()

@app.get("/")
def get_root():
    return {"message": "Welcome to the middleware server! got to /docs to see the API documentation"}

@app.get("/columns")	
def get_authorized_columns():
    return {"columns": AUTHORIZED_COLUMNS}

@app.get("/irrigate")
def get_irrigate():
    # send irrigation control to the mqtt broker via Node-Red
    irrigate()
    return {"message": "The plants are being irrigated!"}

@app.get("/ruptures")
def get_rupture(background_tasks: BackgroundTasks):
    # launch rupture analysis
    taskId = str(uuid.uuid4())
    update_task_status(taskId, "IN_PROGRESS")
    background_tasks.add_task(ruptures, influxDbClient, AUTHORIZED_COLUMNS, taskId)

    return {"message": "Rupture analysis Launched", "taskId": taskId}

@app.get("/correlation")
def get_correlation(param1 : str, param2 : str, background_tasks: BackgroundTasks):
    # raise and error if the param is not authorized
    for param in [param1, param2]:
        if param not in AUTHORIZED_COLUMNS:
            raise HTTPException(status_code=401, detail="Unauthorized column")
    
    # launch correlation analysis
    taskId = str(uuid.uuid4())
    update_task_status(taskId, "IN_PROGRESS")
    background_tasks.add_task(correlation, influxDbClient, param1, param2, taskId)

    return {"message": "Correlation analysis Launched", "taskId": taskId}

@app.get("/status")
def get_status(taskId: str):
    status = get_task_status(taskId)
    if not status:
        raise HTTPException(status_code=404, detail="Task not found")
    return {"status": status}


if __name__ == "__main__":
    uvicorn.run("main:app", host="0.0.0.0", port=8082, reload=True)