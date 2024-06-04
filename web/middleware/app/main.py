import uvicorn
from fastapi import FastAPI, HTTPException
from influxdb import InfluxDBClient
from analysis import correlation, ruptures
from sensor_node import irrigate


app = FastAPI()
influxDbClient = InfluxDBClient(host='localhost', port=8086)
AUTHORIZED_COLUMNS = ['temperature', 'humidity', 'light', 'moisture']

@app.get("/")
def get_root():
    return {"message": "Welcome to the middleware server!"}

@app.get("/irrigate")
def get_irrigate():
    # send irrigation control to the mqtt broker via Node-Red
    irrigate()
    return {"message": "The plants are being irrigated!"}

@app.get("/ruptures")
def get_rupture():
    # launch rupture analysis
    ruptures(AUTHORIZED_COLUMNS)

    return {"message": "Rupture analysis completed"}

@app.get("/correlation")
def get_correlation(param1 : str, param2 : str):
    # raise and error if the param is not authorized
    for param in [param1, param2]:
        if param not in AUTHORIZED_COLUMNS:
            raise HTTPException(status_code=401, detail="Unauthorized column")
    
    # launch correlation analysis
    correlation(influxDbClient, param1, param2)

    return {"message": "Correlation analysis completed"}


if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8082, reload=True)