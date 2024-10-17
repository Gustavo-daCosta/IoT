int tempoLigado = 1000; // 1 segundo
int tempoDesligado = 2000; // 2 segundos

void setup() {
    // Configura o led como output, indicando que é um pino de saída de sinal
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // Liga o led
    digitalWrite(LED_BUILTIN, HIGH);
    // Espera pelo tempo determinado na variável tempoLigado
    delay(tempoLigado);
    // Desliga o led
    digitalWrite(LED_BUILTIN, LOW);
    // Espera pelo tempo determinado na variável tempoDesligado
    delay(tempoDesligado);
}