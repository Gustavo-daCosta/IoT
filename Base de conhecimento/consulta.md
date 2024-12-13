# Conceitos teóricos

## Botão

Um **botão** é um componente eletrônico que atua como um interruptor, permitindo a passagem de corrente elétrica quando pressionado. Existem diferentes tipos de botões, como o **Normalmente Aberto (NA)** e o **Normalmente Fechado (NF)**. O NA fecha o circuito ao ser pressionado, enquanto o NF o abre. Os botões são frequentemente utilizados em projetos com Arduino, onde podem ser configurados com resistores **pull-up** ou **pull-down** para garantir leituras precisas do estado do botão[1][5][7].

## Debounce

O **debounce** é uma técnica utilizada para evitar a leitura incorreta de múltiplos sinais quando um botão é pressionado, devido ao fenômeno conhecido como **efeito bounce**. Esse efeito ocorre porque, ao pressionar um botão mecânico, o contato pode oscilar rapidamente entre os estados aberto e fechado antes de se estabilizar. Para resolver isso, pode-se usar técnicas de debounce via software, como a função `millis()` em Arduino para monitorar o tempo desde a última leitura válida, ou via hardware, utilizando componentes como capacitores e resistores[2][4][6][10].

## Sensores digitais e analógicos

Os **sensores digitais** fornecem dados em forma de valores discretos (geralmente 0 ou 1), enquanto os **sensores analógicos** oferecem uma saída contínua que pode assumir uma infinidade de valores dentro de um intervalo. Por exemplo, um sensor de temperatura digital pode retornar apenas se a temperatura está acima ou abaixo de um determinado valor, enquanto um sensor analógico pode fornecer leituras que variam continuamente com a temperatura real. Essa diferença é crucial na escolha do tipo de sensor para aplicações específicas em projetos eletrônicos.

## I2C

O **I2C** (Inter-Integrated Circuit) é um protocolo de comunicação utilizado para conectar microcontroladores e periféricos em um barramento compartilhado. Ele permite que múltiplos dispositivos se comuniquem usando apenas duas linhas: uma para o clock (SCL) e outra para os dados (SDA). O I2C é amplamente utilizado em projetos com Arduino devido à sua simplicidade e eficiência na comunicação entre dispositivos como sensores e displays.

## Relé

Um **relé** é um interruptor eletromecânico que permite controlar circuitos de alta potência usando sinais de baixa potência. Ele funciona através da energização de uma bobina que atrai uma alavanca, fechando ou abrindo os contatos do circuito. Os relés são frequentemente usados em automação e controle de dispositivos elétricos, como lâmpadas e motores, permitindo que microcontroladores como o Arduino acionem cargas maiores sem risco.

## Encapsulamento

O **encapsulamento** refere-se ao processo de proteger componentes eletrônicos em uma caixa ou invólucro. Isso não apenas protege os componentes contra danos físicos e interferências ambientais, mas também ajuda a organizar circuitos complexos. O encapsulamento é vital para garantir a durabilidade e a funcionalidade dos dispositivos eletrônicos em diversas condições operacionais.

## Millis

A função **millis()** no Arduino retorna o número de milissegundos desde que o dispositivo foi ligado. Essa função é muito útil para temporização sem bloquear a execução do programa, permitindo que outras operações ocorram simultaneamente. É frequentemente utilizada em projetos onde múltiplas tarefas precisam ser gerenciadas ao mesmo tempo, como na implementação do debounce ou no controle de LEDs.

## WiFi

O **WiFi** é uma tecnologia que permite a conexão sem fio à internet ou a redes locais. Em projetos com Arduino, módulos como o ESP8266 ou ESP32 são usados para habilitar conectividade WiFi, permitindo que dispositivos se comuniquem com servidores ou outros dispositivos na rede. Essa capacidade é essencial para aplicações IoT (Internet das Coisas), onde dispositivos precisam enviar e receber dados pela internet.

## MQTT

O MQTT (Message Queuing Telemetry Transport) é um protocolo leve de mensagens projetado para comunicação eficiente entre dispositivos em redes limitadas ou instáveis. É amplamente utilizado em aplicações IoT devido à sua baixa sobrecarga e capacidade de operar em condições adversas. O MQTT permite que dispositivos publiquem mensagens em tópicos específicos e assinem esses tópicos para receber atualizações em tempo real.

## Circuito RC

Um circuito RC consiste em um resistor (R) e um capacitor (C) conectados em série ou paralelo. Esse tipo de circuito é usado para filtrar sinais elétricos e criar atrasos temporais devido à carga e descarga do capacitor através do resistor. A constante de tempo (t = R x C) determina quão rapidamente o circuito responde a mudanças na tensão aplicada. Circuitos RC são fundamentais em muitas aplicações eletrônicas, incluindo temporizadores e filtros[1][8].

# Conceitos práticos


# Pinagem do ESP-32:

| **Pino** | **Função** | **Descrição** |
|----------|------------|----------------|
| GPIO0    | Boot Mode  | Usado para definir o modo de inicialização do ESP32. Deve estar em nível lógico baixo para entrar em modo de gravação. |
| GPIO1    | UART TX    | Pino de transmissão serial (TX) para comunicação UART. |
| GPIO2    | Boot Mode  | Semelhante ao GPIO0, usado para definir o modo de inicialização. |
| GPIO3    | UART RX    | Pino de recepção serial (RX) para comunicação UART. |
| GPIO4    | Touch      | Pino capacitivo que pode ser usado como sensor de toque. |
| GPIO5    | Boot Mode  | Usado para definir o modo de inicialização do ESP32. |
| GPIO12   | Strapping  | Define a tensão do LDO interno durante a inicialização. |
| GPIO13   | PWM        | Pode ser usado para gerar sinais PWM. |
| GPIO14   | PWM        | Pode ser usado para gerar sinais PWM. |
| GPIO15   | Strapping  | Usado para definir o modo de boot; deve estar em nível lógico baixo para gravação. |
| GPIO16   | Touch      | Pino capacitivo que pode ser usado como sensor de toque. |
| GPIO17   | PWM        | Pode ser usado para gerar sinais PWM. |
| GPIO18   | PWM        | Pode ser usado para gerar sinais PWM. |
| GPIO19   | PWM        | Pode ser usado para gerar sinais PWM. |
| GPIO21   | I2C SDA    | Pino padrão para linha de dados I2C. |
| GPIO22   | I2C SCL    | Pino padrão para linha de clock I2C. |
| GPIO23   | SPI MOSI   | Pino de entrada de dados principal para SPI. |
| GPIO24   | SPI MISO   | Pino de saída de dados principal para SPI. |
| GPIO25   | DAC        | Saída digital-analógica (DAC) para gerar sinais analógicos. |
| GPIO26   | DAC        | Saída digital-analógica (DAC) para gerar sinais analógicos. |
| GPIO27   | PWM        | Pode ser usado para gerar sinais PWM. |
| GPIO32   | ADC        | Canal analógico, pode ler sinais analógicos (0-3,3V). |
| GPIO33   | ADC        | Canal analógico, pode ler sinais analógicos (0-3,3V). |
| GPIO34   | ADC        | Somente entrada analógica, não pode ser configurado como saída. |
| GPIO35   | ADC        | Somente entrada analógica, não pode ser configurado como saída. |
| GPIO36   | ADC        | Somente entrada analógica, não pode ser configurado como saída. |
| GPIO39   | ADC        | Somente entrada analógica, não pode ser configurado como saída. |

### Observações
- Os pinos 34 a 39 são apenas entradas e não têm capacidade de pull-up.
- A multiplexação permite que um único pino desempenhe várias funções, dependendo da configuração do software.
- Os pinos 21 e 22 são frequentemente usados como padrão para comunicação I2C devido à compatibilidade com bibliotecas existentes.

Essa tabela resume as funções principais dos pinos do ESP32, permitindo uma rápida referência ao projetar circuitos e sistemas baseados nesse microcontrolador [1][2][3].

# Parte prática

## Componentes

### Botão (e debounce)

Como fazer debounce através do hardware:



Exemplo de debounce por software:

```ino
#define BTN_PIN 8
unsigned long lastDebounceTime = 0;  // Último tempo que o botão foi pressionado
unsigned long debounceDelay = 50;    // Tempo de debounce em milissegundos

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(BTN_PIN);

  if (buttonState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();  // Atualiza o tempo do último pressionamento
    Serial.println("Botão pressionado");
  }
}
```

### 1. **Botão com debounce**
O debounce garante que o ESP32 interprete apenas um sinal ao pressionar um botão, evitando leituras erradas devido a ruídos.

#### Código
```cpp
#define BUTTON_PIN 12 // Pino do botão
#define LED_PIN 13    // Pino do LED

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // 50ms
int buttonState = LOW;
int lastButtonState = LOW;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      }
    }
  }
  lastButtonState = reading;
}
```

#### Montagem
- Conecte um botão com uma extremidade ao pino D12 do ESP32 e a outra ao GND.
- Um LED ao pino D13 com resistor de 220Ω e o outro terminal ao GND.

---

### 2. **Sensores digitais e analógicos**
#### Código
```cpp
#define DIGITAL_SENSOR_PIN 14
#define ANALOG_SENSOR_PIN 32

void setup() {
  pinMode(DIGITAL_SENSOR_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  int digitalValue = digitalRead(DIGITAL_SENSOR_PIN);
  int analogValue = analogRead(ANALOG_SENSOR_PIN);

  Serial.print("Digital: ");
  Serial.print(digitalValue);
  Serial.print(" | Analog: ");
  Serial.println(analogValue);

  delay(500);
}
```

#### Montagem
- Sensor digital ao pino D14, com um pull-down resistor (10kΩ) entre o pino e GND.
- Sensor analógico ao pino ADC32.

---

### 3. **I2C**
#### Código
```cpp
#include <Wire.h>

#define I2C_ADDRESS 0x27

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("I2C Scanner");

  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(i, HEX);
    }
  }
}

void loop() {}
```

#### Montagem
- Conecte os pinos SDA e SCL ao ESP32 (D21 e D22 por padrão).
- Verifique o endereço do dispositivo.

---

### 4. **Relé**
#### Código
```cpp
#define RELAY_PIN 5

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH); // Liga
  delay(1000);
  digitalWrite(RELAY_PIN, LOW); // Desliga
  delay(1000);
}
```

#### Montagem
- O pino IN do relé ao D5 do ESP32.
- Ligue a carga no relé conforme indicado no módulo.

---

### 5. **Encapsulamento**
Crie classes para abstrair funcionalidades, por exemplo, para um LED.

#### Código
```cpp
class LED {
  int pin;

public:
  LED(int p) : pin(p) { pinMode(pin, OUTPUT); }
  void on() { digitalWrite(pin, HIGH); }
  void off() { digitalWrite(pin, LOW); }
};

LED myLED(13);

void setup() {
  Serial.begin(115200);
  myLED.on();
}

void loop() {
  delay(1000);
  myLED.off();
  delay(1000);
  myLED.on();
}
```

---

### 6. **Millis**
#### Código
```cpp
#define LED_PIN 13
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}
```

---

### 7. **WiFi**
#### Código
```cpp
#include <WiFi.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}

void loop() {}
```

---

### 8. **MQTT**
#### Código
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      client.subscribe("test/topic");
    } else {
      delay(5000);
    }
  }
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  client.setServer(mqtt_server, 1883);
  reconnect();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  client.publish("test/topic", "Hello from ESP32");
  delay(2000);
}
```

#### Montagem
- Conecte o ESP32 à rede Wi-Fi e verifique logs no terminal.