#include "sensorsManager.h"
#include "networkManager.h"

SensorsManager sensorsManager;
WiFiController wc = WiFiController("rpi-server", "raspberry");
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

  Serial.print("Let's init the broker at ");
  Serial.println(wc.getGatewayIP());
  IPAddress gatewayIP = wc.getGatewayIP();
  char ipStr[16];
  sprintf(ipStr, "%d.%d.%d.%d", gatewayIP[0], gatewayIP[1], gatewayIP[2], gatewayIP[3]);
  broker.init(ipStr, 1883);
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
    Serial.println("Humidite du sol = " + String(sensorsManager.getSoilMoisture())+ " %RH");
    Serial.println("PH = " + String(sensorsManager.getPH()));

    StaticJsonDocument<80> doc = sensorsManager.exportJsonData();

    broker.setData(doc);
    broker.publish("/home/sensors");
  }
}
