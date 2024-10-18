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

## Segunda parte

Na segunda parte, deve-se utilizar um led externo ao Arduino, do qual vai conectado em uma das portas digitais do Arduino e deve cumprir a mesma tarefa, piscando de forma intermitente, ficando ligado por um tempo X e desligado por um tempo Y.

Para o led externo, se torna necessária a utilização de um resistor para passar somente a corrente necessária para o led, evitando que ele queime.
Para ligar o led, é necessária uma tensão elétrica mínima de 1,2V e máxima de 3,6V, dito isso, para definir a resistência ideal do resistor, foi utilizada a média entre a tensão mínima e a máxima, resultado em 2,4V.

**Cálculo do resistor:**

Considerando uma tensão de entrada de 5V e uma tensão de saíde de 2,4V:

$V_R = 5V - 2,4V = 2,6V$

Um led normalmente possui corrente de 20mA, sendo assim \( I = 0,02A \)

A lei de Ohm nos dá a seguinte fórmula para calcular a resistência necessária:

$R = \frac{V_R}{I}$

Substituindo os valores:

$R = \frac{2,6V}{0,02A} = 130\ \Omega$

Por fim, conclui-se que é necessário um resistor de 130 ohms para fazer o led funcionar na tensão e corrente adequada.

**Código utilizado:**

```ino
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
```

**Vídeo demonstrando o funcionamento do circuito no Tinkercad:**

https://github.com/user-attachments/assets/f22da2b6-0286-4e54-89e2-dcb07e5f4f01

**Vídeo demonstrando o funcionamento do circuito físico:**

https://github.com/user-attachments/assets/52eb6313-88f7-4231-8a87-ad71aa0956a7
