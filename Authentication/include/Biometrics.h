#ifndef BIOMETRICS_H
#define BIOMETRICS_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

class Biometrics {
    private:
        Adafruit_Fingerprint fingerprint;
        uint8_t getFingerprintID();

    public:
        Biometrics(Stream &serial); // Construtor
        void setup();
        bool isFingerDetected();
        void ReadFingerprint();
};

#endif