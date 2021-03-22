#ifndef MOTORS_HPP
#define MOTORS_HPP

#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/Motor.hpp"
#define MAX_SPEED 250
#define MAX_PWM   255

using namespace webots;

Motor *leftMotor;
Motor *rightMotor;

double map(int x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int constrain(int input, int minimumValue, int maximumValue)
{
    if (input >= maximumValue)
        return maximumValue;
    if (input <= minimumValue)
        return minimumValue;
    return input;
}

double convertPWMinSpeed(int pwm)
{
    return map(pwm, -MAX_PWM, MAX_PWM, -MAX_SPEED, MAX_SPEED);
}

void driveMotors(int leftPWM, int rightPWM)
{
    leftPWM = constrain(leftPWM, -MAX_PWM, MAX_PWM);
    rightPWM = constrain(rightPWM, -MAX_PWM, MAX_PWM);
    int leftSpeed = convertPWMinSpeed(leftPWM);
    int rightSpeed = convertPWMinSpeed(rightPWM);
    leftMotor->setVelocity(leftSpeed);
    rightMotor->setVelocity(rightSpeed);
}

void stop()
{
    leftMotor->setVelocity(0);
    rightMotor->setVelocity(0);
}

Motor *initMotor(Robot *robot, char *motorName)
{
    Motor *motor = robot->getMotor(motorName);
    motor->setPosition(INFINITY);
    motor->setVelocity(0);
    return motor;
}

void initMotors(Robot *robot)
{
    leftMotor = initMotor(robot, (char *)"left wheel motor");
    rightMotor = initMotor(robot, (char *)"right wheel motor");
}

#endif
