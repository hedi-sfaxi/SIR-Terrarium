#include "networkManager.h"

WiFiController::WiFiController(const char *ssid, const char *password)
{
    this->ssid = ssid;
    this->password = password;
    Serial.print("hello");
}

// connect to a network
void WiFiController::connect()
{
    WiFi.begin(this->ssid, this->password);
}

// check if the network is connected
bool WiFiController::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

// get the local IP address
IPAddress WiFiController::getLocalIP()
{
    return WiFi.localIP();
}

// get the IP address of the gateway
IPAddress WiFiController::getGatewayIP()
{
    return WiFi.gatewayIP();
}

// setters
void WiFiController::setPassword(const char *password)
{
    this->password = password;
}

void WiFiController::setSSID(const char *ssid)
{
    this->ssid = ssid;
}

DataBroker::DataBroker(const char *mqtt_server, const int mqtt_port)
{
    this->mqtt_server = mqtt_server;
    this->mqtt_port = mqtt_port;
}

void DataBroker::init()
{
    this->client.setServer(this->mqtt_server, this->mqtt_port);
}

bool DataBroker::isConnected()
{
    return this->client.connected();
}

void DataBroker::setData(StaticJsonDocument<80> data)
{
    this->data = data;
}

void DataBroker::reconnect()
{
    do
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            delay(5000);
        }
        Serial.println();
    } while (!this->client.connected());
}

void DataBroker::publish(const char *topic)
{
    char buffer[80];
    serializeJson(this->data, buffer);
    this->client.publish(topic, buffer);
}
