#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

class MQTT {
    private:
        MQTT(WiFiClientSecure& espClient, const char* server, int port, const char* user, const char* pass); // Construtor privado
        static MQTT* instance; // Instância estática
        PubSubClient client;
        
        const char* _mqtt_server;
        int _mqtt_port;
        const char* _mqtt_user;
        const char* _mqtt_pass;
        WiFiClientSecure& _espClient;

    public:
        static MQTT* getInstance(WiFiClientSecure& espClient, const char* server, int port, const char* user, const char* pass);
        void setup();
        void reconnect();
        void sendMessage(const char* topic, const char* msg);
        void loop();
};

#endif
