#include "sensorsManager.h"

void SensorsManager::init() {
    Serial.println("Initializing sensors");
    
    Wire.begin(6, 7);       // Initialize the I2C communication
    dhtSensor.begin();      // Initialize the DHT sensor

    // Initialize the BH1750 sensor
    bool avail = lightSensor.begin(BH1750_TO_GROUND);
    if (!lightSensor.begin(BH1750_TO_GROUND)) Serial.println("[Error] No BH1750 sensor found!");

    EEPROM.begin(32);//needed to permit storage of calibration value in eeprom
	  ph.begin();
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

float SensorsManager::getPH() {
      float voltage, phValue, temperature;
      temperature = getTemperature();         
      voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage
      phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
      ph.calibration(voltage,temperature);       // calibration process by Serail CMD
      return phValue;
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
    doc["p"] = getPH();
    return doc;
}
