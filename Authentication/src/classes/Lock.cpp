#include "Lock.h"
#include <Arduino.h>

Lock::Lock() : lock(22) {}

void Lock::setup() {
    pinMode(lock, OUTPUT);
}

void Lock::changeLockState(bool isOpen) {
    digitalWrite(lock, isOpen ? HIGH : LOW);
}
