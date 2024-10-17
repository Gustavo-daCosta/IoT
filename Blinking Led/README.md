# Blinking Led

Atividade ponderada, visando utilizar um Arduino para piscar um led.

## Primeira parte

Na primeira parte, o led acoplado ao Arduino deve piscar de forma intermitente, devendo ficar ligado por um tempo X e desligado por um tempo Y.

**Código utilizado:**

```ino
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
```

**Vídeo demonstrando o funcionamento do circuito no Tinkercad:**

https://github.com/user-attachments/assets/95887982-fb61-422a-8eb8-dade10d806fb

**Vídeo demonstrando o funcionamento do circuito físico:**

https://github.com/user-attachments/assets/b986be45-6349-44f8-8c6e-c1b5f7d562d6
