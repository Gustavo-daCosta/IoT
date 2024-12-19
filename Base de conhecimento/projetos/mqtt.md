```markdown
# Conexão ao MQTT no ESP32 com Controle de LEDs

Este guia explica como configurar a conexão MQTT no ESP32 utilizando o framework Arduino e a biblioteca PubSubClient. Também implementamos um controle básico de LEDs e envio de mensagens para o broker MQTT.

## Pré-requisitos

1. ESP32
2. Biblioteca **PubSubClient**
3. Rede Wi-Fi disponível
4. Broker MQTT (usamos `mqtt-dashboard.com` como exemplo)

---

## Etapas para Configurar a Conexão MQTT

### 1. Importar as Bibliotecas

Importe as bibliotecas necessárias para gerenciar a conexão Wi-Fi e o cliente MQTT:

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
```

### 2. Configurar a Conexão Wi-Fi

Defina as credenciais da sua rede Wi-Fi:

```cpp
const char *SSID = "SeuSSID";
const char *PASSWORD = "SuaSenha";
```

No código, a função para reconectar ao Wi-Fi garante que o ESP32 permaneça conectado:

```cpp
void reconnectWiFi() {
  if (WiFi.status() == WL_CONNECTED)
    return;
  
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Reconectando...");
  }
  Serial.println("Conectado ao Wi-Fi!");
}
```

### 3. Configurar o Broker MQTT

Defina as configurações do broker:

```cpp
#define BROKER_PORT 1883
const char *BROKER_ADDRESS = "mqtt-dashboard.com";
```

Inicialize o cliente MQTT:

```cpp
WiFiClient device_client;
PubSubClient MQTT(device_client);

void initMQTT() {
  MQTT.setServer(BROKER_ADDRESS, BROKER_PORT);          
}
```

```markdown
### 4. Configurar a Conexão Wi-Fi

Defina as credenciais da sua rede Wi-Fi e implemente uma função para reconectar automaticamente caso a conexão seja perdida:

```cpp
const char *SSID = "SeuSSID";
const char *PASSWORD = "SuaSenha";

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
```

Essa função é chamada durante o `setup()` e no loop principal para garantir conectividade contínua.

---

### 5. Configurar o Cliente MQTT

Defina as configurações do broker MQTT e implemente funções para conectar e verificar a conectividade:

```cpp
#define BROKER_ADDRESS "mqtt-dashboard.com"
#define BROKER_PORT 1883
#define ID_DEVICE "ESP32_LED_Controller"

WiFiClient espClient;
PubSubClient MQTT(espClient);

void initMQTT() {
  MQTT.setServer(BROKER_ADDRESS, BROKER_PORT);
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (MQTT.connect(ID_DEVICE)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(MQTT.state());
      delay(2000);
    }
  }
}
```

A função `reconnectMQTT()` tenta se conectar ao broker MQTT enquanto não estiver conectado.

---

### 6. Publicar e Assinar Tópicos

Use os métodos da biblioteca **PubSubClient** para enviar e receber mensagens MQTT:

```cpp
#define TOPIC_LED_A "home/ledA"
#define TOPIC_LED_B "home/ledB"

void publishMessages() {
  MQTT.publish(TOPIC_LED_A, "ON");
  MQTT.publish(TOPIC_LED_B, "OFF");
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
```

Configure o callback no `setup()` para tratar mensagens recebidas:

```cpp
MQTT.setCallback(callback);
```

---

### 7. Ciclo Principal (`loop`)

No `loop()`, mantenha a conectividade Wi-Fi e MQTT, e publique mensagens periodicamente:

```cpp
void loop() {
  if (!MQTT.connected()) {
    reconnectMQTT();
  }
  MQTT.loop();
  
  publishMessages();
  delay(2000); // Intervalo entre publicações
}
```
