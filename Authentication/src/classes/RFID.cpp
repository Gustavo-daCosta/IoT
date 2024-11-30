#include "RFID.h"

RFID::RFID(byte ssPin, byte rstPin) : rfid(ssPin, rstPin) {}

void RFID::setup() {
    Serial.println("Iniciando sensor RFID");
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("Sensor RFID configurado");
}

bool RFID::isRfidDetected() {
    return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

void RFID::readRfid() {
    String cardUID = getRfidUID();

    if (cardUID.isEmpty()) {
        Serial.println("Nenhum cartão detectado");
        return;
    }

    Serial.print("Cartão detectado com UID");
    Serial.println(cardUID);

    // Lógica de autenticação do UID lido
}

String RFID::getRfidUID() {
    if (!isRfidDetected()) return "";

    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    rfid.PICC_HaltA();
    return uid;
}
