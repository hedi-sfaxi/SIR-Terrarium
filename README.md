# SIR-Terrarium

This repository contains the work of students as part of their project to set up a monitoring stack for a terrarium.

## Documentation

### ESP32

#### Prerequisites

1. Install Arduino IDE from [official page](https://www.arduino.cc/en/software) according to your OS
2. Add and select the board manager for your ESP32 in Tools > Board
3. Install these libraries (it depends of the sensors you are using):
    - "**DHT sensor library**"   from *Adafruit*
    - "**hp_BH1750**" from *Stefan Armborat*
4. Upload the "ESP32" files code from the git to your ESP32


#### Getting Started

The esp 32 is a sensor node to retrieve data from the terrarium. The code uploaded to it launches automatically when connected to a power source.

#### Technical

The code is divided in 3 parts : the esp32.ino file, a NetworkManager and a SensorsManager.
We explain those 3 parts here below.

##### esp32.ino

This is the .ino file, it is the principal one which uses the functions of the managers to make the sensor node work correctly.

##### SensorsManager

This manager is responsible for gathering all the used sensors's APIs.  
Beyond the getters for each sensor, SensorsManager also provides the SensorsManager::exportJsonData, which is responsible for providing all the gathered data from the sensors as a StaticJsonDocument, which will then be sent to the raspberry-pi server through the NetworkManager broker.

##### NetworkManager

Here we manage all the work linked to data transmission. It’s divided in 2 classes, the WifiController that handles the wifi connection and the DataBroker used to publish data to the raspberry-pi server. The principal methods here are DataBroker::reconnect which handles the MQTT connection and DataBroker::publish sends the data to a topic after it has been set in the main by the SensorsManager.

### Raspberry Pi

This section is meant to show you the steps to install, configure and deploy a fully containerized monitoring stack using docker-compose. It includes the following elements :   

Mosquitto : MQTT broker to receive data from the ESP32.

Node-Red : It’s a flow-based development tool. We’ll be using it to subscribe to the MQTT topics on the Mosquitto broker and convert the data format and then forward the processed data to a time-series database : InfluxDB.

InfluxDB : It will be our TSDB to store the processed sensor data received from Node-RED.

Grafana : Finally, this tool connects to InfluxDB to visualize the stored sensor data. Grafana allows you to create dynamic and interactive dashboards, providing real-time insights and historical trends based on the data collected from the ESP32 sensors.


##### Prerequisites

To setup your monitoring stack on your RaspberryPi you’ll first need :  

1. A RaspberryPi with an embedded Wi-Fi card or an external Wi-Fi adapter and an internet connexion

2. Install Docker and Docker-Compose on the RaspberryPi following the official Docker documentation : https://docs.docker.com/compose/install/

3. Clone the project GitHub project

##### Getting Started

After cloning the project go to the raspberry directory 

```
sir@raspberrypi:~/SIR-Terrarium $ cd raspberry/
sir@raspberrypi:~/SIR-Terrarium/raspberry $ ls
backups  docker-compose.yml  services  volumes
```

Once here, just launch the docker-compose up -d command 

```
sir@raspberrypi:~/SIR-Terrarium/raspberry $ docker-compose up -d
[+] Running 5/0
 ✔ Container mosquitto     Running                                                                      0.0s 
 ✔ Container nodered       Running                                                                      0.0s 
 ✔ Container nginx         Running                                                                      0.0s 
 ✔ Container grafana       Running                                                                      0.0s 
 ✔ Container influxdb      Running                                                                      0.0s

```

##### Configurations

###### Node-Red, Mosquitto
To configure your mosquitto instance and and the data flow all the way to your influxDB database, just access the Node-Red configuration UI on the port 1880 of your raspberry. You'll find three blocs that you should configure according to the IP adresse of your raspberry, your message queue topics names and the json data your are fetching.

###### InfluxDB
To check if data is being written in the database, enter the influxDB container and execute the following commands :
```
docker exec -it influxdb influx
USE sensor_data
show measurements
select * from sensor_data
quit
```

###### Grafana
Now that everything is set up, you can visualize the data on the grafana url at port 3000 of your RaspberryPi. You can also modify the dashboard using this interface.



