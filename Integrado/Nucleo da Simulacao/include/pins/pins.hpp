#ifndef PINS_HPP
#define PINS_HPP

namespace pins
{
// Definição de pinos para os robôs sumo 3Kg
#ifdef SUMO3KG
    int leftMotor  = 18;
    int rightMotor = 19;
    int leftEdge   = 33;
    int rightEdge  = 32;
#endif

// Definição de pinos para os robôs sumo mini
#ifdef SUMOMINI
    int leftMotor  = 9;
    int rightMotor = 10;
    int leftEdge   = 5;
    int rightEdge  = 6;
#endif
};

#endif
