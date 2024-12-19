#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Display {
    private:
        LiquidCrystal_I2C lcd;
        unsigned long startTime;
        int period;

        Display();

    public:
        static Display& getInstance();
        void setup();
        void writeMessage(const char* message1, const char* message2 = "", int period = 0);
        void clearDisplay();
        void update();

        // Proíbe a criação de novas instâncias da classe Display
        Display(const Display&) = delete;
        Display& operator = (const Display&) = delete;
};

#endif
