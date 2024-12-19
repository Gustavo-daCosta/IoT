#include <WiFi.h>
#include <PubSubClient.h>

class Led {
  public:
    int ledPin;
    bool ledStatus = LOW;
    Led(int pin) {
      ledPin = pin; 
    }

    void beginLed() {
      pinMode(ledPin, OUTPUT);
    }

    void turnLedOn() {
      digitalWrite(ledPin, HIGH);
      ledStatus = HIGH;
    }
    void turnLedOff() {
      digitalWrite(ledPin, LOW);
      ledStatus = LOW;
    }

    void blinkLed() {
      delay(500);
      if (ledStatus) {
        turnLedOff();
        return;
      }
      turnLedOn();
    }
};

#define LDR     "LDR"
#define LED_A     "LED_A"
#define LED_B     "LED_B"
#define ID_DEVICE         ""

#define BROKER_PORT 1883
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";
const char *BROKER_ADDRESS = "mqtt-dashboard.com";
int timer = 0;

#define LDR_PIN 32

WiFiClient device_client;
PubSubClient MQTT(device_client);
Led ledA(12);
Led ledB(14);


void initMQTT() {
  //Inicia a conexão com o broker mqtt
  MQTT.setServer(BROKER_ADDRESS, BROKER_PORT);          
}

void reconnectMQTT() {
  //Enquanto não está conectado
  while (!MQTT.connected()) {
    //Tenta se conectar ao mqtt
    if (!MQTT.connect(ID_DEVICE)) {
      Serial.println("Reconectando no MQTT...");
      delay(200);
    }
  }
}

void checkWiFIAndMQTT() {
  if (!MQTT.connected())
    reconnectMQTT();
  reconnectWiFi();
}

void reconnectWiFi() {
  if (WiFi.status() == WL_CONNECTED)
    return;
  
  //Se conecta ao wifi
  WiFi.begin(SSID, PASSWORD);
  
  //Fica reconectando no wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Reconectando");
  }
  Serial.println("Conectado no wifi");
}


void setup() {
  Serial.begin(115200);
  Serial.print("Iniciou");
  
  pinMode(LDR_PIN, INPUT);
  pinMode(2, INPUT);
  pinMode(25, OUTPUT);
  ledA.beginLed();
  ledB.beginLed();
  reconnectWiFi();
  initMQTT();
  checkWiFIAndMQTT();
  timer = millis();
}


void loop() {
  int time = timer - millis();
  int timeHasPassed = abs(time);

  float ldrRead = analogRead(LDR_PIN);
  Serial.println(ldrRead);

  if (ldrRead > 2048) {
    ledA.blinkLed();
    ledB.turnLedOff();
  } else {
    ledA.turnLedOff();
    ledB.turnLedOn();
  }

  if (digitalRead(2)) {
    Serial.println("relé apertado");
    digitalWrite(25, HIGH);
  } else {
    digitalWrite(25, LOW);
  }

  if (timeHasPassed > 1000) {
    char ldrChar[10];
    String(ldrRead).toCharArray(ldrChar, 10);

    char ledAValue[2];
    String(ledA.ledStatus).toCharArray(ledAValue, 2);
    
    char ledBValue[2];
    String(ledB.ledStatus).toCharArray(ledBValue, 2);


    MQTT.publish(LDR, ldrChar);
    MQTT.publish(LED_A, ledAValue);
    MQTT.publish(LED_B, ledBValue);
    checkWiFIAndMQTT();
    timer = millis();
  }
  delay(200);
}