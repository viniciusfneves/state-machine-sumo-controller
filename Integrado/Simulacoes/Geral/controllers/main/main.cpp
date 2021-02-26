// Biblioteca de integração do Arduino
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include "../../../../Nucleo da Simulacao/include/webots/motors.hpp"
#include "../../../../Nucleo da Simulacao/include/webots/sensors.hpp"
#include "../../../../Nucleo da Simulacao/include/event_handler/event_handler.hpp"

#define TIME_STEP 1

using namespace webots;

int main(int argc, char **argv) {

  Robot *robot = new Robot();
  // Lógica geral de inicialização
  initMotors(robot);
  initSensors(robot, TIME_STEP);
  initTime(robot, TIME_STEP);
  while (robot->step(TIME_STEP) != -1) {
    handle_events();
  }

  delete robot;
  return 0;
}