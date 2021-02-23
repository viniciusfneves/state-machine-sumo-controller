#ifndef MOTORS_HPP
#define MOTORS_HPP

#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/Motor.hpp"
#include <iostream>
#include "../pins/pins.hpp"
#define MAX_SPEED 6.28 * 1.3

using namespace webots;

using namespace std;

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

void move(double leftSpeed, double rightSpeed)
{
    leftMotor->setVelocity(leftSpeed * MAX_SPEED);
    rightMotor->setVelocity(rightSpeed * MAX_SPEED);
}

void moveLeftMotor(double leftSpeed)
{
    //cout << "LEFT: " << leftSpeed;
    leftMotor->setVelocity(leftSpeed * MAX_SPEED);
}

void moveRightMotor(double rightSpeed)
{
    //cout << " RIGHT: " << rightSpeed << endl;
    rightMotor->setVelocity(rightSpeed * MAX_SPEED);
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
    leftMotor = initMotor(robot, (char *)"wheel1");
    rightMotor = initMotor(robot, (char *)"wheel2");
}

void analogWrite(int pin, int pwm)
{
    if (pin == pins::leftMotor)
        moveLeftMotor(convertPWMinSpeed(pwm));
    else if (pin == pins::rightMotor)
        moveRightMotor(convertPWMinSpeed(pwm));
}

#endif
