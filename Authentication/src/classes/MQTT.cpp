#include "MQTT.h"

// Inicialização da instância estática como nula
MQTT* MQTT::instance = nullptr;

MQTT::MQTT(WiFiClientSecure& espClient, const char* server, int port, const char* user, const char* pass)
    : client(espClient), _mqtt_server(server), _mqtt_port(port), _mqtt_user(user), _mqtt_pass(pass), _espClient(espClient) {}

MQTT* MQTT::getInstance(WiFiClientSecure& espClient, const char* server, int port, const char* user, const char* pass) {
    if (instance == nullptr) {
        instance = new MQTT(espClient, server, port, user, pass); // Cria a instância se não existir
    }
    return instance;
}

void MQTT::setup() {
    _espClient.setInsecure();
    client.setServer(_mqtt_server, _mqtt_port);
    client.setCallback(callback);
}

void MQTT::reconnect() {
    while (!client.connected()) {
        Serial.print("Tentando conexão com o Broker...");
        if (client.connect("ESP32Client", _mqtt_user, _mqtt_pass)) {
            Serial.println("Conectado ao Broker!");
            client.subscribe("exodia/rfid");
            client.subscribe("exodia/biometria");
        } else {
            Serial.print("Falha ao conectar. Return Code: ");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

void MQTT::sendMessage(const char* topic, const char* msg) {
    if (client.publish(topic, msg)) {
        Serial.print("Mensagem enviada: ");
        Serial.println(msg);
    } else {
        Serial.println("Erro ao enviar a mensagem!");
    }
}

void MQTT::loop() {
    client.loop();
}

void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Mensagem vinda do tópico: ");
    Serial.println(topic);
    String messageReceived = "";
    for (int i = 0; i < length; i++) {
        messageReceived += (char)message[i];
    }
    Serial.println(messageReceived);
}
