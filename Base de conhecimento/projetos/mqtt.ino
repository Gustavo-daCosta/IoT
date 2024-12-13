#include <WiFi.h>
#include <PubSubClient.h>

const char *SSID = "SeuSSID";
const char *PASSWORD = "SuaSenha";
#define BROKER_ADDRESS "mqtt-dashboard.com"
#define BROKER_PORT 1883
#define ID_DEVICE "ESP32_LED_Controller"

WiFiClient espClient;
PubSubClient MQTT(espClient);

#define TOPIC_LED_A "home/ledA"
#define TOPIC_LED_B "home/ledB"

void reconnectWiFi() {
  if (WiFi.status() == WL_CONNECTED)
    return;
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Reconectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi.");
}

void initMQTT() {
  MQTT.setServer(BROKER_ADDRESS, BROKER_PORT);
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (MQTT.connect(ID_DEVICE)) {
      Serial.println("Conectado!");
      MQTT.subscribe(TOPIC_LED_A);
      MQTT.subscribe(TOPIC_LED_B);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(MQTT.state());
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida: ");
  Serial.print(topic);
  Serial.print(" -> ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void publishMessages() {
  MQTT.publish(TOPIC_LED_A, "ON");
  MQTT.publish(TOPIC_LED_B, "OFF");
}

void setup() {
  Serial.begin(115200);
  reconnectWiFi();
  initMQTT();
  MQTT.setCallback(callback);
}

void loop() {
  if (!MQTT.connected()) {
    reconnectMQTT();
  }
  MQTT.loop();
  publishMessages();
  delay(2000);
}
