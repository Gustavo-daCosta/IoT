#ifndef LED_H
#define LED_H

#include <Arduino.h>

enum LedColor {
    RED,
    GREEN,
    BLUE
};

class Led {
private:
    const int ledRed = 33;
    const int ledGreen = 26;
    const int ledBlue = 27;
    unsigned long startTime;
    int period;
    Led();

public:
    static Led& getInstance();
    void setup();
    void writeToLed(int ledRedValue, int ledGreenValue, int ledBlueValue);
    void turnOnLed(LedColor color, int period = 0);
    void turnOffLed();
    void update();

    // Proíbe a criação de novas instâncias da classe Led
    Led(const Led&) = delete;
    Led& operator = (const Led&) = delete;
};

#endif