#ifndef PINS_HPP
#define PINS_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif

namespace pins
{
// Definição de pinos para os robôs sumo 3Kg
#ifdef SUMO3KG
    int leftMotor  = 18;
    int rightMotor = 19;
#endif

// Definição de pinos para os robôs sumo mini
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
