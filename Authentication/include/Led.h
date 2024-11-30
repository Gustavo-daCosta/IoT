#ifndef LED_H
#define LED_H

enum LedColor {RED, GREEN, BLUE};

class Led {
    private:
        const int ledRed = 13;
        const int ledGreen = 15;
        const int ledBlue = 5;

    protected:
        void writeToLed(int ledRedValue, int ledGreenValue, int ledBlueValue);

    public:
        Led(int ledRed, int ledGreen, int ledBlue);
        void setup();
        void turnOnLed(LedColor color);
        void turnOffLed();
};

#endif