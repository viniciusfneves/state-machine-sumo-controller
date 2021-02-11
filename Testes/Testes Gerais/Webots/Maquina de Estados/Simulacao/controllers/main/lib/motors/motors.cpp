#include "motors.hpp"

void move(Motor *leftMotor, double leftSpeed, Motor *rightMotor, double rightSpeed) {
  leftMotor->setVelocity(leftSpeed*MAX_SPEED);
  rightMotor->setVelocity(rightSpeed*MAX_SPEED);
}

Motor *initMotor(Robot *robot, char *motorName) {
  Motor *motor = robot->getMotor(motorName);
  motor->setPosition(INFINITY);
  return motor;
}