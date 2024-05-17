#include "sensorsManager.h"

SensorsManager sensorsManager;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setting up");
  sensorsManager.init();
}

void loop()
{
    // Light intensity measurement
    Serial.println("Luminosite flag");
    Serial.println("Luminosite = " + String(sensorsManager.getLightIntensity()) + " lux");

    // Temperature and humidity measurement
    Serial.println("Temperature = " + String(sensorsManager.getTemperature()) + " °C");
    Serial.println("Humidite de l'air = " + String(sensorsManager.getHumidity()) + " %");

    // Soil moisture measurement
    Serial.println("Humidite du sol = " + String(sensorsManager.getSoilMoisture()));

    delay(2000); // Delay to slow down the loop for easier reading
}
