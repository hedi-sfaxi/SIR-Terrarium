#include "networkManager.h"

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

void DataBroker::init(const char *mqtt_server, const int mqtt_port)
{
    this->client.setServer(mqtt_server, mqtt_port);
}

bool DataBroker::isConnected()
{
    return this->client.connected();
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
