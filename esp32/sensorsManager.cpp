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

float SensorsManager::getSoilMoisture() {
    // Read the raw value from the sensor connected to pin A0, for example
    int rawValue = analogRead(0);

    // Extreme sensor values for air and water
    int airValue = 2590;  // Sensor value in free air (dry)
    int waterValue = 1297;  // Sensor value in water (saturated)

    // Calculate the relative humidity as a percentage
    float humidity = ((float)(airValue - rawValue) / (airValue - waterValue)) * 100.0;

    // Ensure that the humidity does not exceed 100% or fall below 0%
    humidity = constrain(humidity, 0.0, 100.0);

    return humidity;
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
