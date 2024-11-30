#include "Biometrics.h"

Biometrics::Biometrics(Stream &serial) : fingerprint(&serial) {}

void Biometrics::setup() {
    Serial.println("Iniciando sensor biométrico...");
    fingerprint.begin(57600);

    if (fingerprint.verifyPassword()) {
        Serial.println("Sensor biométrico encontrado");
    } else {
        Serial.println("Falha ao encontrar o sensor biométrico");
        // Esse loop é pra parar o programa mesmo, avaliar a necessidade dele e estudar melhores maneiras de lidar com isso
        while (true);
    }
}

bool Biometrics::isFingerDetected() {
    return fingerprint.getImage() == FINGERPRINT_OK;
}

void Biometrics::ReadFingerprint() {
    uint8_t id = getFingerprintID();

    if (id == FINGERPRINT_NOFINGER) {
        Serial.println("Nenhum digital detectada");
    } else if (id == FINGERPRINT_OK) {
        Serial.print("Digital autenticada com o ID: ");
        Serial.println(fingerprint.fingerID);

        // Aqui tenho que chamar a classe da trava eletrônica/relé (ainda não fiz)
    } else {
        Serial.println("Falha na autenticação. Tente novamente");
    }
}

uint8_t Biometrics::getFingerprintID() {
    if (fingerprint.getImage() != FINGERPRINT_OK) return FINGERPRINT_NOFINGER;
    if (fingerprint.image2Tz() != FINGERPRINT_OK) return FINGERPRINT_IMAGEFAIL;
    if (fingerprint.fingerFastSearch() != FINGERPRINT_OK) return FINGERPRINT_NOTFOUND;

    return FINGERPRINT_OK;
}
