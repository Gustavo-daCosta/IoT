#include <Arduino.h>
#include "Biometrics.h"
#include "RFID.h"

// BIOMETRIA - Definição dos pinos e criação das instâncias das classes
const int RX_PIN = 16; // Corrigir (pino incorreto)
const int TX_PIN = 17; // Corrigir (pino incorreto)

HardwareSerial fingerprintSerial(2);
Biometrics biometrics(fingerprintSerial);

// RFID - Definição dos pinos e criação das instâncias das classes
const int SS_PIN = 5; // Corrigir (pino incorreto)
const int RST_PIN = 22; // Corrigir (pino incorreto)

RFID rfid(SS_PIN, RST_PIN);

bool onlyRead = true;

void setup() {
  Serial.begin(115200);
  fingerprintSerial.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN);

  biometrics.setup();
  rfid.setup();
}

void loop() {
  if (onlyRead) {
    if (biometrics.isFingerDetected()) {
      Serial.println("Digital detectada, iniciando autenticação");
      biometrics.ReadFingerprint();
    }

    if (rfid.isRfidDetected()) {
      Serial.println("Token RFID detectado, iniciando autenticação");
      rfid.readRfid();
    }

    delay(100);
  } else {
    // Lógica de cadastro

    // Tem que fazer alguma lógica para receber do front se a pessoa quer cadastrar
    // a biometria ou um token RFID
  }
}
