// Biblioteca de integração do Arduino
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include "../../../../Nucleo da Simulacao/include/webots/motors.hpp"
#include "../../../../Nucleo da Simulacao/include/webots/sensors.hpp"
#include "../../../../Nucleo da Simulacao/include/event_handler/event_handler.hpp"
#include "../../../../Nucleo da Simulacao/include/events/events.hpp"

#define TIME_STEP 1

using namespace webots;

int main(int argc, char **argv) {

  Robot *robot = new Robot();
  // Lógica geral de inicialização
  initMotors(robot);
  initSensors(robot, TIME_STEP);
  initTime(robot, TIME_STEP);
  addEventToQueue(Event::Start);
  while (robot->step(TIME_STEP) != -1) {
    readEdgeSensors();
    readOpponentSensors();
    processMachineEvents();
  }

  delete robot;
  return 0;
}