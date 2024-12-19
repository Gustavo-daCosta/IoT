#include "Led.h"

Led::Led()
    : startTime(0), period(0) {}

void Led::setup() {
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledBlue, OUTPUT);
    turnOffLed();
}

void Led::writeToLed(int ledRedValue, int ledGreenValue, int ledBlueValue) {
    analogWrite(ledRed, ledRedValue);
    analogWrite(ledGreen, ledGreenValue);
    analogWrite(ledBlue, ledBlueValue);
}

void Led::turnOnLed(LedColor color, int period) {
    switch (color) {
        case RED:
            writeToLed(255, 0, 0);
            break;
        case GREEN:
            writeToLed(0, 255, 0);
            break;
        case BLUE:
            writeToLed(0, 0, 255);
            break;
        default:
            turnOffLed();
            break;
    }
    
    if (period > 0) {
        this -> period = period;
        if (startTime == 0) startTime = millis();
    }
}

void Led::turnOffLed() {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    startTime = 0;
    period = 0;
}

void Led::update() {
    if (period > 0 && millis() - startTime >= period) {
        turnOffLed();
    }
}
