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