#ifndef PINS_HPP
#define PINS_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif

namespace pins
{
#ifdef SUMO3KG
    int leftMotor  = 18;
    int rightMotor = 19;
#endif

#ifdef SUMOMINI
    int leftMotor  = 9;
    int rightMotor = 10;
#endif

#ifndef REAL_ROBOT
    int leftMotor  = 9;
    int rightMotor = 10;
#endif
};

#endif
