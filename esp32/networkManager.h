#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <PubSubClient.h>

class WiFiController
{
public:
    inline WiFiController(const char *ssid, const char *password)
    {
        this->ssid = ssid;
        this->password = password;
    };

    void connect();
    bool isConnected();
    IPAddress getLocalIP();
    IPAddress getGatewayIP();
    inline void setPassword(const char *password) { this->password = password; };
    inline void setSSID(const char *ssid) { this->ssid = ssid; };

private:
    const char *ssid;
    const char *password;
};

class DataBroker // TODO: Change the class name and update the main
{

public:
    inline DataBroker(){};

    void reconnect();
    void publish(const char *topic);
    bool isConnected();
    inline void setData(StaticJsonDocument<80> data) { this->data = data; };
    void init(const char *mqtt_server, const int mqtt_port);
    void callback(char *topic, byte *payload, unsigned int length);
    inline void listen() { this->client.loop(); };

private:
    WiFiClient espClient;
    PubSubClient client = PubSubClient(espClient);
    StaticJsonDocument<80> data;
};

#endif