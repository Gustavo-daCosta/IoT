#include <Adafruit_Fingerprint.h>
#include "Biometrics.h"
#include "Display.h"
#include "Led.h"
#include "Lock.h"

// Construtor da classe Biometrics
Biometrics::Biometrics(Stream &serial) : fingerprint(&serial) {}

// Função para configurar o sensor biométrico
void Biometrics::setup() {
    Serial.println("Iniciando sensor biométrico...");
    fingerprint.begin(57600);

    if (fingerprint.verifyPassword()) {
        Serial.println("Sensor biométrico encontrado");
    } else {
        Serial.println("Falha ao encontrar o sensor biométrico");
        display.writeMessage("Erro ao conectar", "Sensor biométrico");
        // Esse loop é pra parar o programa mesmo, avaliar a necessidade dele e estudar melhores maneiras de lidar com isso
        while (true);
    }
}

// Função para detectar quando o sensor detecta uma biometria no sensor
bool Biometrics::isFingerDetected() {
    return fingerprint.getImage() == FINGERPRINT_OK;
}

// Função para ler e validar uma biometria
void Biometrics::readFingerprint() {
    display.setup();
    uint8_t id = getFingerprintID(); // ID da biometria

    switch (id) {
        case FINGERPRINT_NOFINGER:
            Serial.println("Nenhuma digital detectada");
            display.writeMessage("Encoste o dedo", "...", 2000);
            led.turnOnLed(BLUE, 2000);
            break;

        case FINGERPRINT_OK:
            Serial.print("Digital autenticada com o ID:");
            Serial.println(fingerprint.fingerID);
            led.turnOnLed(GREEN, 2000);
            display.writeMessage("Biometria autenticada", "com sucesso", 2000);
            break;

        case FINGERPRINT_NOTFOUND:
            Serial.println("Digital não reconhecida. Tente novamente");
            display.writeMessage("Digital não", "reconhecida", 2000);
            led.turnOnLed(RED, 2000);
            break;

        default:
            Serial.println("Erro ao ler a digital");
            display.writeMessage("Erro ao ler", "a digital", 2000);
            led.turnOnLed(RED, 2000);
            delay(2000);
    }

    led.update();
    display.update();
}

// Função para cadastrar uma nova biometria
void Biometrics::registerFingerprint() {
    
    int id = findAvailableID();
    if (id == -1) {
        Serial.println("Todos os IDs estão ocupados. Não é possível cadastrar mais digitais.");
        return;
    }

    Serial.print("Usando o ID disponível: ");
    Serial.println(id);

    // Etapa 1: Captura da primeira imagem da digital
    while (fingerprint.getImage() != FINGERPRINT_OK);
    if (fingerprint.image2Tz(1) != FINGERPRINT_OK) {
        Serial.println("Erro ao processar imagem. Tente novamente.");
        return;
    }

    // Etapa 2: Captura da segunda imagem da digital
    Serial.println("Remova o dedo e coloque novamente.");
    delay(2000);
    while (fingerprint.getImage() != FINGERPRINT_OK);
    if (fingerprint.image2Tz(2) != FINGERPRINT_OK) {
        Serial.println("Erro ao processar imagem. Tente novamente.");
        return;
    }

    // Etapa 3: Criação do modelo
    if (fingerprint.createModel() != FINGERPRINT_OK) {
        Serial.println("Erro ao criar o modelo da digital.");
        return;
    }

    // Etapa 4: Armazena o modelo no ID especificado
    if (fingerprint.storeModel(id) != FINGERPRINT_OK) {
        Serial.println("Erro ao armazenar a digital no sensor.");
        return;
    }

    Serial.println("Sucesso no cadastro da digital!");
}

// Função para encontrar o próximo ID disponível
int Biometrics::findAvailableID() {
    if (fingerprint.getTemplateCount() >= 127) {
        Serial.println("Todos os IDs estão ocupados.");
        return -1;
    }

    for (int i = 1; i <= 127; i++) {
        if (fingerprint.loadModel(i) != FINGERPRINT_OK) {
            return i;
        }
    }
}

// Função para capturar o ID da biometria
uint8_t Biometrics::getFingerprintID() {
    if (fingerprint.getImage() != FINGERPRINT_OK) {
        Serial.println("Erro: Nenhuma imagem capturada.");
        return FINGERPRINT_NOFINGER;
    }
    if (fingerprint.image2Tz() != FINGERPRINT_OK) {
        Serial.println("Erro: Conversão de imagem falhou.");
        return FINGERPRINT_IMAGEFAIL;
    }
    if (fingerprint.fingerFastSearch() != FINGERPRINT_OK) {
        Serial.println("Erro: Digital não encontrada.");
        return FINGERPRINT_NOTFOUND;
    }

    return FINGERPRINT_OK;
}
