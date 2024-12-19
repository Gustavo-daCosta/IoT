#ifndef BIOMETRICS_H
#define BIOMETRICS_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include "Led.h"
#include "Display.h"
#include "Lock.h"

class Biometrics {
    private:
        Adafruit_Fingerprint fingerprint;
        uint8_t getFingerprintID();
    
        Led& led = Led::getInstance();
        Display& display = Display::getInstance();
        Lock& lock = Lock::getInstance();
        int findAvailableID();

    public:
        Biometrics(Stream &serial);
        void setup();
        bool isFingerDetected();
        void readFingerprint();
        void registerFingerprint();
};

#endif