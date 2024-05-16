#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <PubSubClient.h>

class WiFiController
{
public:
    WiFiController(const char *ssid, const char *password);

    void connect();
    bool isConnected();
    IPAddress getLocalIP();
    IPAddress getGatewayIP();
    void setPassword(const char *password);
    void setSSID(const char *ssid);

private:
    const char *ssid;
    const char *password;
};

class DataBroker
{

public:
    DataBroker(const char *mqtt_server, int mqtt_port);

    void reconnect();
    void publish(const char *topic);
    bool isConnected();
    void setData(StaticJsonDocument<80> data);
    void init();

private:
    const char *mqtt_server;
    int mqtt_port;
    WiFiClient espClient;
    PubSubClient client = PubSubClient(espClient);
    StaticJsonDocument<80> data;
};

#endif