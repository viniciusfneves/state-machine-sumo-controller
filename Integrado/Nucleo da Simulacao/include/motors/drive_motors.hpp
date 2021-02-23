#ifndef DRIVE_MOTORS_HPP
#define DRIVE_MOTORS_HPP

#include "../pins/pins.hpp"
#ifndef REAL_ROBOT
#include "../webots/motors.hpp"
#endif

void drive(int PWM_esq, int PWM_dir)
{
#ifdef REAL_ROBOT
    analogWrite(pins::leftMotor, PWM_esq);
    analogWrite(pins::rightMotor, PWM_dir);
#endif
};

void stop()
{
#ifdef REAL_ROBOT
    analogWrite(pins::leftMotor, 0);
    analogWrite(pins::rightMotor, 0);
#endif
};

#endif