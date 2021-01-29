#include <integratedMain.hpp>

void setup() {
  // Implementação exclusiva do Arduino que não impacta a lógica restante do código
  pinMode(pin::led, OUTPUT); 

  // Lógica geral de inicialização
  initCode();
}

void loop() {
  loopCode();
}