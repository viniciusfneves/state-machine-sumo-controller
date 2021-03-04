#ifndef PINS_HPP
#define PINS_HPP
#include <Arduino.h> //Todo arquivo que importar pins, terá Arduino.h como dependencia automaticamente

namespace pins
{
// Definição de pinos para os robôs sumo 3Kg
#ifdef SUMO3KG
    namespace motors
    {
        int leftMotor = 25;
        int rightMotor = 26;
    }
    namespace edgeSensors
    {
        int leftEdge = 33;
        int rightEdge = 32;
    }
    namespace opponentsSensors
    {
        int farLeft = 23;
        int left = 22;
        int center = 21;
        int right = 19;
        int farRight = 18;

        int sensors[] = {farLeft, left, center, right, farRight};
    }
#endif

// Definição de pinos para os robôs sumo mini
#ifdef SUMOMINI
    int leftMotor = 9;
    int rightMotor = 10;
    int leftEdge = 5;
    int rightEdge = 6;
#endif
};

#endif
