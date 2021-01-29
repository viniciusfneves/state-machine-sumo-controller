// Biblioteca de integração do Arduino
#include "../../../Robo_Blink/lib/integratedMain/integratedMain.hpp"

#define TIME_STEP 64

int main(int argc, char **argv) {

  // Lógica geral de inicialização
  initCode();
  
  while (robot->step(TIME_STEP) != -1) {
    loopCode();
  }

  delete robot;
  return 0;
}