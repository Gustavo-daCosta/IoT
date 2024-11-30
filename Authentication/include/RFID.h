#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <MFRC522.h>

class RFID {
    private:
        MFRC522 rfid;
        String lastCardUID;

    public:
        RFID(byte ssPin, byte rstPin);
        void setup();
        bool isRfidDetected();
        void readRfid();
        String getRfidUID();
};

#endif