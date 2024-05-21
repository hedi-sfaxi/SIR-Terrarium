#include "sensorsManager.h"
#include "networkManager.h"

SensorsManager sensorsManager;
WiFiController wc = WiFiController("Mot de passe = free", "azera123");
DataBroker broker;
long lastMsg = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Setting up");
  sensorsManager.init();

  Serial.println();
  Serial.print("Connecting");
  wc.connect();
  while (!wc.isConnected())
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(wc.getLocalIP());

  Serial.println("Let's init the broker");
  broker.init("192.168.85.85", 1883);
}

void loop()
{
  if (!broker.isConnected())
  {
    broker.reconnect();
  }

  long now = millis();

  if (now - lastMsg > 5000)
  {
    lastMsg = now;
    // Light intensity measurement
    Serial.println("Luminosite = " + String(sensorsManager.getLightIntensity()) + " lux");

    // Temperature and humidity measurement
    Serial.println("Temperature = " + String(sensorsManager.getTemperature()) + " °C");
    Serial.println("Humidite de l'air = " + String(sensorsManager.getHumidity()) + " %");

    // Soil moisture measurement
    Serial.println("Humidite du sol = " + String(sensorsManager.getSoilMoisture()));

    StaticJsonDocument<80> doc = sensorsManager.exportJsonData();

    broker.setData(doc);
    broker.publish("/home/sensors");
  }
}
