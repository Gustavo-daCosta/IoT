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
