# Semáforo Offline

Montagem física de um semáforo utilizando LEDs e resistores em 
uma protoboard, considerando que os LEDs devem seguir o mesmo padrão de cores das luzes de um semáforo.

## Parte 1: Montagem Física do Semáforo

### 1.1 Lista de materiais

| **Material**             | **Quantidade** |
| ------------------------ | -------------- |
| Arduino UNO              | 1              |
| LED                      | 3              |
| Jumper Macho-Macho       | 6              |
| Resistor                 | 3              |
| Buzzer                   | 1              |

### 1.2 Montagem

A montagem consistiu em encaixar os LEDs na estrutura do semáforo e conectar os LEDs na protoboard e os LEDs foram conectados na placa do Arduino através dos resistores. Por fim, o Buzzer foi colocado na Protoboard, se aproveitando da trilha dos LEDs para puxar o GND e um novo jumper foi colocado para conectar o Buzzer a um pino do Arduino.

---

## Parte 2: Programação e Lógica do Semáforo

Código da aplicação:

```ino
int ledsOrder[] = {11, 12, 13, 13, 12};
int tones[] = {40, 130, 220, 220, 130};
int buzzer = 7;

void setup() {
  for (int i = 0; i < 3; i++) pinMode(ledsOrder[i], OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    // Liga o LED
    digitalWrite(ledsOrder[i], HIGH);
    // Toca o buzzer por 500 milisegundos
    tone(buzzer, tones[i], 500);
    // Espera um período determinado
    delay(ledsOrder[i] == 13 ? 6000 : 2000);
    // Desliga o LED
    digitalWrite(ledsOrder[i], LOW);
  }
}
```

## Resultado final


---

## Avaliação de pares

**Júlia Lika Ishikawa:**
- Montagem física: 4/4 pontos
- Temporização: 3/3 pontos
- Código: 3/3 pontos

**Total:** 10 pontos

**Bruno Fabiani:**
- Montagem física: 4/4 pontos
- Temporização: 3/3 pontos
- Código: 3/3 pontos

**Total:** 10 pontos
