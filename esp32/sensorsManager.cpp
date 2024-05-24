#include "sensorsManager.h"

void SensorsManager::init() {
    Serial.println("Initializing sensors");
    
    Wire.begin(6, 7);       // Initialize the I2C communication
    dhtSensor.begin();      // Initialize the DHT sensor

    // Initialize the BH1750 sensor
    bool avail = lightSensor.begin(BH1750_TO_GROUND);
    if (!lightSensor.begin(BH1750_TO_GROUND)) Serial.println("[Error] No BH1750 sensor found!");
}

float SensorsManager::getLightIntensity() {
    lightSensor.start();
    return lightSensor.getLux();
}

float SensorsManager::getTemperature() {
    return dhtSensor.readTemperature();
}

float SensorsManager::getHumidity() {
    return dhtSensor.readHumidity();
}

int SensorsManager::getSoilMoisture() {
    return analogRead(0);
}

StaticJsonDocument<80> SensorsManager::exportJsonData() {
    StaticJsonDocument<80> doc;
    doc["l"] = getLightIntensity();
    doc["t"] = getTemperature();
    doc["h"] = getHumidity();
    doc["m"] = getSoilMoisture();
    return doc;
}
