// Biblioteca de integração do Arduino
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

#include "../../../../Nucleo/include/event_handler/event_handler.hpp"
#include "../../../../Nucleo/include/events/events.hpp"
#include "../../../../Nucleo/include/webots/motors.hpp"
#include "../../../../Nucleo/include/webots/sensors.hpp"

using namespace webots;

int main(int argc, char **argv) {
    Robot *robot = new Robot();
    const int timeStep = (int)robot->getBasicTimeStep();

    // Lógica geral de inicialização
    initMotors(robot);
    initSensors(robot, timeStep);
    initTime(robot);
    addEventToQueue(Event::Start);
    while (robot->step(timeStep) != -1) {
        readEdgeSensors();
        readOpponentSensors();
        processMachineEvents();
    }

    delete robot;
    return 0;
}