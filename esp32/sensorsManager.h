#ifndef SENSORS_MANAGER_H
#define SENSORS_MANAGER_H

#include <hp_BH1750.h> // Include the library for the BH1750 light sensor
#include <Wire.h>      // Include the Wire library for I2C
#include "DHT.h"       // Include the DHT library for humidity and temperature
#include <ArduinoJson.h>

#define DHTPIN 10     // Change this to the pin you have connected the DHT sensor to
#define DHTTYPE DHT11 // Change this to whatever type of DHT sensor you are using (DHT11, DHT22, etc.)

class SensorsManager {
    private:
        hp_BH1750 lightSensor{};
        DHT dhtSensor{DHTPIN, DHTTYPE};

    public:
        inline SensorsManager(){};

        void init();

        // hp_BH1750 lightSensor 
        float getLightIntensity();

        // DHT sensor
        float getTemperature();
        float getHumidity();

        // Soil moisture sensor
        int getSoilMoisture();

        // exportJsonData
        StaticJsonDocument<80> exportJsonData();
};

#endif
