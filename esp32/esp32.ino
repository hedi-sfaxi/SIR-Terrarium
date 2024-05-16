#include <Arduino.h>
#include <hp_BH1750.h> // Include the library for the BH1750 light sensor
#include <Wire.h>      // Include the Wire library for I2C
#include "DHT.h"       // Include the DHT library for humidity and temperature

#define DHTPIN 10     // Change this to the pin you have connected the DHT sensor to
#define DHTTYPE DHT11 // Change this to whatever type of DHT sensor you are using (DHT11, DHT22, etc.)

DHT dht(DHTPIN, DHTTYPE); // Create the DHT sensor object
hp_BH1750 BH1750;         //  create the sensor

void setup()
{
    Serial.begin(115200);
    Wire.begin(6, 7); // Initialize the I2C communication
    dht.begin();      // Initialize the DHT sensor
    // Initialize the BH1750 sensor
    bool avail = BH1750.begin(BH1750_TO_GROUND);
    if (!avail)
    {
        Serial.println("No BH1750 sensor found!");
        while (true)
        {
        };
    }
}

void loop()
{
    // Light intensity measurement
    BH1750.start();
    float lux = BH1750.getLux();
    Serial.println("Luminosite = " + String(lux) + " lux");

    // Temperature and humidity measurement
    Serial.println("Temperature = " + String(dht.readTemperature()) + " °C");
    Serial.println("Humidite de l'air = " + String(dht.readHumidity()) + " %");

    // Soil moisture measurement
    int soilMoistureValue;
    soilMoistureValue = analogRead(0); // connect sensor to Analog 0
    Serial.println("Humidite du sol = " + String(soilMoistureValue));

    delay(2000); // Delay to slow down the loop for easier reading
}
