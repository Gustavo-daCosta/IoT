#include <Arduino.h>

// Estrutura para gerenciar o timer
struct Timer {
  unsigned long period = 0;     // Período do timer
  unsigned long startTime = 0;  // Tempo de início
  bool isRunning = false;       // Flag para indicar se o timer está ativo
  void (*callback)() = nullptr; // Ponteiro para função de callback
};

void timer(unsigned long period) {
  // Implementação simples de um timer global
  static Timer globalTimer;
  
  // Inicializa o timer com o período especificado
  globalTimer.period = period;
  globalTimer.startTime = millis();
  globalTimer.isRunning = true;
}

// Sobrecarga para adicionar um callback
void timer(unsigned long period, void (*callback)()) {
  static Timer globalTimer;
  
  // Inicializa o timer com período e callback
  globalTimer.period = period;
  globalTimer.startTime = millis();
  globalTimer.isRunning = true;
  globalTimer.callback = callback;
}

// Função para verificar e executar o timer
void checkTimer() {
  static Timer globalTimer;
  
  // Verifica se o timer está ativo
  if (globalTimer.isRunning && globalTimer.period > 0) {
    // Verifica se o tempo decorrido atingiu o período
    if (millis() - globalTimer.startTime >= globalTimer.period) {
      // Executa o callback se existir
      if (globalTimer.callback != nullptr) {
        globalTimer.callback();
      }
      
      // Para o timer
      globalTimer.isRunning = false;
      globalTimer.startTime = 0;
    }
  }
}
