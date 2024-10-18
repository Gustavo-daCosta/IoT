int tempoLigado = 1000; // 1 segundo
int tempoDesligado = 2000; // 2 segundos
int pinoLed = 13;

void setup() {
    // Configura o led como output, indicando que é um pino de saída de sinal
    pinMode(pinoLed, OUTPUT);
}

void loop() {
    // Liga o led
    digitalWrite(pinoLed, HIGH);
    // Espera pelo tempo determinado na variável tempoLigado
    delay(tempoLigado);
    // Desliga o led
    digitalWrite(pinoLed, LOW);
    // Espera pelo tempo determinado na variável tempoDesligado
    delay(tempoDesligado);
}
