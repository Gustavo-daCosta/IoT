#include <Arduino.h>
#include "Biometrics.h"
#include "RFID.h"
#include "Display.h"
#include "Led.h"

// BIOMETRIA - Definição dos pinos e criação das instâncias das classes
const int RX_PIN = 16;
const int TX_PIN = 17;

HardwareSerial fingerprintSerial(2);
Biometrics biometrics(fingerprintSerial);

// RFID - Definição dos pinos e criação das instâncias das classes
const int SS_PIN = 5;
const int RST_PIN = 22;

// Se não rolar, move isso para o setup()
RFID rfid(SS_PIN, RST_PIN);
Display& display = Display::getInstance();
Led& led = Led::getInstance();

bool onlyRead = true;

void setup() {
  Serial.begin(115200);
  fingerprintSerial.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN);

  led.setup();
  display.setup();
  biometrics.setup();
  rfid.setup();
}

void loop() {
  onlyRead ? readMode() : registerMode();
  delay(100);
}

// Função que encapsula a lógica de leitura
void readMode() {
  if (biometrics.isFingerDetected()) {
    Serial.println("Digital detectada, iniciando autenticação");
    biometrics.readFingerprint();
  }

  if (rfid.isRfidDetected()) {
    Serial.println("Token RFID detectado, iniciando autenticação");
    rfid.readRfid();
  }
}

// Função que encapsula a lógica de cadastro
void registerMode() {
  if (biometrics.isFingerDetected()) {
    Serial.println("Digital detectada, iniciando cadastro");
    biometrics.registerFingerprint();
  }

  if (rfid.isRfidDetected()) {
    Serial.println("Token RFID detectado, iniciando cadastro");
    rfid.registerRfid();
  }

  // Tem que fazer alguma lógica para receber do front se a pessoa quer cadastrar
}
