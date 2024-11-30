#include "Led.h"
#include <Arduino.h>

Led::Led(int ledRed, int ledGreen, int ledBlue)
    : ledRed(ledRed), ledGreen(ledGreen), ledBlue(ledBlue) {}

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

void Led::turnOnLed(LedColor color) {
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
}

void Led::turnOffLed() {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
}
