#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include "motors/motors.hpp"

using namespace webots;
#define TIME_STEP 64

double speed = 0.9;

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  
  Motor *leftMotor = initMotor(robot, (char *) "left wheel motor");
  Motor *rightMotor = initMotor(robot, (char *) "right wheel motor");
  
  move(leftMotor, speed, rightMotor, speed);
  
  while (robot->step(TIME_STEP) != -1);

  delete robot;
  return 0;
}
