#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <MFRC522.h>
#include <WiFi.h>

// Classe para controle do display LCD
class LCDDisplay {
private:
    LiquidCrystal_I2C lcd;
public:
    LCDDisplay(uint8_t address, uint8_t cols, uint8_t rows) : lcd(address, cols, rows) {}
    void init() {
        lcd.init();
        lcd.backlight();
    }
    void showMessage(const char* message) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(message);
        Serial.println(message);
    }
};

// Classe para conexão WiFi
class WiFiConnection {
private:
    const char* ssid;
    const char* password;
    LCDDisplay& display;

public:
    WiFiConnection(const char* ssid, const char* password, LCDDisplay& display)
        : ssid(ssid), password(password), display(display) {}

    void connect() {
        Serial.print("Conectando a ");
        Serial.println(ssid);
        display.showMessage("Conectando ao WiFi...");

        WiFi.begin(ssid, password);
        int attempt = 0;

        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
            attempt++;
            if (attempt > 10) {
                display.showMessage("WiFi Falhou!");
                return;
            }
        }
        display.showMessage("WiFi Conectado!");
    }

    bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
    }
};

// Classe para controle do LED RGB
class LedRGB {
private:
    int pinRed, pinGreen, pinBlue;
public:
    LedRGB(int red, int green, int blue) : pinRed(red), pinGreen(green), pinBlue(blue) {}

    void init() {
        pinMode(pinRed, OUTPUT);
        pinMode(pinGreen, OUTPUT);
        pinMode(pinBlue, OUTPUT);
    }

    void setColor(bool red, bool green, bool blue) {
        digitalWrite(pinRed, red ? HIGH : LOW);
        digitalWrite(pinGreen, green ? HIGH : LOW);
        digitalWrite(pinBlue, blue ? HIGH : LOW);
    }
};

// Classe para controle do buzzer
class Buzzer {
private:
    int pin;
public:
    Buzzer(int pin) : pin(pin) {}

    void init() {
        pinMode(pin, OUTPUT);
    }

    void beep(int duration = 100) {
        digitalWrite(pin, HIGH);
        delay(duration);
        digitalWrite(pin, LOW);
    }
};

// Classe para controle do sensor biométrico
class BiometricSensor {
private:
    Adafruit_Fingerprint finger;
    LCDDisplay& display;
public:
    BiometricSensor(HardwareSerial* serial, LCDDisplay& display)
        : finger(serial), display(display) {}

    void init() {
        finger.begin(57600);
        if (!finger.verifyPassword()) {
            Serial.println("Erro Biometrico");
            while (true);
        }
        Serial.println("Biometrico OK");
    }

    bool authenticate() {
        display.showMessage("Posicione o dedo...");
        int result;

        while (true) {
            result = finger.getImage();
            if (result == FINGERPRINT_NOFINGER) {
                delay(500);
            } else if (result == FINGERPRINT_OK) {
                break;
            } else {
                display.showMessage("Erro na leitura");
                delay(1000);
                return false;
            }
        }

        result = finger.image2Tz();
        if (result != FINGERPRINT_OK) {
            display.showMessage("Erro ao processar");
            delay(1000);
            return false;
        }

        result = finger.fingerSearch();
        if (result == FINGERPRINT_OK) {
            char buffer[16];
            sprintf(buffer, "ID: %d", finger.fingerID);
            display.showMessage(buffer);
            delay(2000);
            return true;
        } else {
            display.showMessage("Nao encontrado");
            delay(1000);
            return false;
        }
    }
};

// Classe para controle do sensor RFID
class RFIDSensor {
private:
    MFRC522 rfid;
public:
    RFIDSensor(uint8_t sda, uint8_t rst) : rfid(sda, rst) {}

    void init() {
        SPI.begin();
        rfid.PCD_Init();
    }

    String readUID() {
        if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
            return "";
        }
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            uid += String(rfid.uid.uidByte[i], HEX);
        }
        rfid.PICC_HaltA();
        return uid;
    }
};

// Classe principal para o sistema
class AccessSystem {
private:
    LCDDisplay display;
    WiFiConnection wifi;
    LedRGB led;
    Buzzer buzzer;
    BiometricSensor biometrics;
    RFIDSensor rfid;

    const int relayPin;
    const int buttonPin;

public:
    AccessSystem()
        : display(0x27, 16, 2),
          wifi("SHARE-RESIDENTE", "Share@Residente23", display),
          led(33, 32, 27),
          buzzer(26),
          biometrics(&Serial1, display),
          rfid(21, 22),
          relayPin(25),
          buttonPin(34) {}

    void init() {
        Serial.begin(115200);
        pinMode(relayPin, OUTPUT);
        pinMode(buttonPin, INPUT);

        display.init();
        led.init();
        buzzer.init();
        biometrics.init();
        rfid.init();
        wifi.connect();
        display.showMessage("Sistema OK");
        delay(2000);
    }

    void run() {
        if (!wifi.isConnected()) {
            Serial.println("WiFi desconectado! Tentando reconectar...");
            wifi.connect();
        }

        if (digitalRead(buttonPin) == HIGH) {
            display.showMessage("Cadastro...");
            delay(2000);
        }

        String rfidUID = rfid.readUID();
        if (rfidUID != "") {
            handleAccess("RFID OK, Acesso!");
        }

        if (biometrics.authenticate()) {
            handleAccess("Biometria OK, Acesso!");
        } else {
            display.showMessage("Biometria Nao!");
            led.setColor(true, false, false);
            buzzer.beep(200);
            delay(2000);
            led.setColor(false, false, false);
        }

        delay(500);
    }

private:
    void handleAccess(const char* message) {
        display.showMessage(message);
        led.setColor(false, true, false);
        buzzer.beep();
        digitalWrite(relayPin, HIGH);
        delay(5000);
        digitalWrite(relayPin, LOW);
        led.setColor(false, false, false);
    }
};

AccessSystem system;

void setup() {
    system.init();
}

void loop() {
    system.run();
}
