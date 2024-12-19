#include "Display.h"

// Endereço do display e dimensões (16 colunas x 2 linhas)
#define DISPLAY_ADDRESS 0x27
#define DISPLAY_COLUMNS 16
#define DISPLAY_ROWS 2

// Construtor
Display::Display() : lcd(DISPLAY_ADDRESS, DISPLAY_COLUMNS, DISPLAY_ROWS), startTime(0), period(0) {}

Display& Display::getInstance() {
    static Display instance;
    return instance;
}

// Configurações iniciais do display
void Display::setup() {
    lcd.init();        // Inicializa o display
    lcd.clear();       // Limpa o display
    lcd.backlight();   // Ativa a luz de fundo
}

// Exibe uma mensagem no display
void Display::writeMessage(const char* message1, const char* message2, int period) {
    lcd.clear(); // Limpa o display antes de exibir nova mensagem
    lcd.setCursor(0, 0);
    lcd.print(message1);
    if (message2[0] != '\0') { // Verifica se há uma segunda linha
        lcd.setCursor(0, 1);
        lcd.print(message2);
    }

    if (period > 0) {
        this->period = period;
        startTime = millis();
    }
}

// Limpa o display e redefine temporizadores
void Display::clearDisplay() {
    lcd.clear();
    startTime = 0;
    period = 0;
}

// Atualiza o display após o período especificado
void Display::update() {
    if (period > 0 && millis() - startTime >= period) {
        clearDisplay();
    }
}
