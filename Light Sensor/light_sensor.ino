#include <Arduino.h>

int sensorLuz = A0;
int valorSensorLuz = 0;
int pinoLed = 7;

void setup() {
    Serial.begin(9600);
    pinMode(sensorLuz, INPUT);
    pinMode(pinoLed, OUTPUT);
}

void loop() {
    valorSensorLuz = analogRead(sensorLuz);
    Serial.println(valorSensorLuz);
    digitalWrite(pinoLed, valorSensorLuz > 100);
    delay(50);
}