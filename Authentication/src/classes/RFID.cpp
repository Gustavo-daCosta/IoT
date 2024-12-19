#include "RFID.h"

// Construtor da classe RFID
RFID::RFID(byte ssPin, byte rstPin) : rfid(ssPin, rstPin) {}

// Configuração inicial do sensor RFID
void RFID::setup() {
    Serial.println("Iniciando sensor RFID...");
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("Sensor RFID configurado");
}

// Verifica se um cartão RFID foi detectado
bool RFID::isRfidDetected() {
    return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

// Lê o UID do cartão RFID
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

// Lê o cartão RFID e autentica o UID
void RFID::readRfid() {
    String cardUID = getRfidUID();

    if (cardUID.isEmpty()) {
        Serial.println("Nenhum cartão detectado");
        display.writeMessage("Nenhum cartão", "detectado", 2000);
        led.turnOnLed(RED, 2000);
        return;
    }

    Serial.print("Cartão detectado com UID: ");
    Serial.println(cardUID);

    if (isAuthorized(cardUID)) {
        Serial.println("Acesso autorizado!");
        display.writeMessage("Acesso", "autorizado", 2000);
        //lock.unlock();
        led.turnOnLed(GREEN, 2000);
    } else {
        Serial.println("Acesso negado!");
        display.writeMessage("Acesso", "negado", 2000);
        led.turnOnLed(RED, 2000);
    }
}

// Registra um novo cartão RFID
void RFID::registerRfid() {
    String cardUID = getRfidUID();

    if (cardUID.isEmpty()) {
        Serial.println("Nenhum cartão detectado para cadastro");
        display.writeMessage("Nenhum cartão", "detectado", 2000);
        led.turnOnLed(RED, 2000);
        return;
    }

    Serial.print("Cartão detectado para cadastro com UID: ");
    Serial.println(cardUID);

    if (isAuthorized(cardUID)) {
        Serial.println("Cartão já cadastrado!");
        display.writeMessage("Cartão já", "cadastrado", 2000);
        led.turnOnLed(RED, 2000);
        return;
    }

    // Gerar um hash aleatório para o cartão
    String randomValue = generateRandomHash();
    Serial.print("Gerando valor aleatório para o cartão: ");
    Serial.println(randomValue);

    // Gravar o hash no cartão
    if (writeHashToCard(randomValue)) {
        authorizedUids.push_back(cardUID);
        Serial.println("Cartão cadastrado com sucesso!");
        display.writeMessage("Cartão", "cadastrado", 2000);
        led.turnOnLed(GREEN, 2000);
    } else {
        Serial.println("Falha ao cadastrar o cartão!");
        display.writeMessage("Erro ao", "cadastrar", 2000);
        led.turnOnLed(RED, 2000);
    }
}

// Verifica se um UID é autorizado
bool RFID::isAuthorized(const String &uid) {
    for (const String &authUid : authorizedUids) {
        if (authUid == uid) {
            return true;
        }
    }
    return false;
}

// Gera um hash aleatório para atribuir ao cartão
String RFID::generateRandomHash() {
    String hash = "";
    for (int i = 0; i < 8; i++) {
        char randomChar = random(0, 16); // Gera números hexadecimais de 0 a F
        hash += String(randomChar, HEX);
    }
    hash.toUpperCase();
    return hash;
}

// Grava o hash no cartão
bool RFID::writeHashToCard(const String &hash) {
    // Autentica o setor 1 usando a chave padrão
    MFRC522::MIFARE_Key sectorKey;
    for (byte i = 0; i < 6; i++) {
        sectorKey.keyByte[i] = 0xFF;
    }
    byte block = 4; // Escolhendo o bloco 4 para gravar o hash
    byte buffer[16] = {0};

    // Converte o hash para um buffer de 16 bytes (pode truncar ou completar com zeros)
    for (size_t i = 0; i < hash.length() && i < 16; i++) {
        if (!rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &sectorKey, &(rfid.uid))) {}
    }

    // Escreve os dados no bloco especificado
    MFRC522::StatusCode status = rfid.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("Erro ao gravar no cartão: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    Serial.println("Hash gravado com sucesso no cartão!");
    return true;
}
