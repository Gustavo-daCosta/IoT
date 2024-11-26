#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

const char* ssid = "Inteli.Iot";
const char* password = ""; // Senha foi removida para subir o código no github

#define IO_SERVER      "io.adafruit.com"
#define IO_SERVERPORT  1883
#define IO_USERNAME  "" // Usuário foi removido para subir o código no github
#define IO_KEY       "" // Chave foi removida para subir o código no github

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);
Adafruit_MQTT_Publish wifiRSSI = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/RSSI");

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void connectToMQTT() {
  while (mqtt.connected() == false) {
    Serial.print("Conectando ao MQTT...");
    int8_t ret = mqtt.connect();
    if (ret == 0) {
      Serial.println("MQTT Connected!");
    } else {
      Serial.println(mqtt.connectErrorString(ret));
      Serial.println("Tentando conexão ao RSSI novamente em 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  connectToMQTT();
}

void loop() {
  if (!mqtt.connected()) connectToMQTT();

  mqtt.processPackets(10);
  mqtt.ping();
  
  int rssi = WiFi.RSSI();

  if (!wifiRSSI.publish((int32_t)rssi)) {
    Serial.println("Erro ao publicar RSSI");
  } else {
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println("dBm");
  }

  delay(2000);
}
