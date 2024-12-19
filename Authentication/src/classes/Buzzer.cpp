#include <Arduino.h>
#include "Buzzer.h"

Buzzer::Buzzer() : buzzerPin(buzzerPin) {}

Buzzer& Buzzer::getInstance() {
    static Buzzer instance;
    return instance;
}

void Buzzer::setup() {
    pinMode(buzzerPin, OUTPUT);
}

void Buzzer::playSound(int soundTone, int period) {
    tone(buzzerPin, soundTone, period);
}
