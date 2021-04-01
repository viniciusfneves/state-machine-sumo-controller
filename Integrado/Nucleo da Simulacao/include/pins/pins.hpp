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
        int servo = 27;
    }
    namespace edgeSensors
    {
        int leftFrontEdge = 35;
        int rightFrontEdge = 34;
        int leftRearEdge = 39;
        int rightRearEdge = 36;
    }
    namespace opponentsSensors
    {
        int leftSide = 5;
        int farLeft = 12;
        int left = 13;
        int center = 14;
        int right = 15;
        int farRight = 18;
        int rightSide = 19;

        int sensors[] = {farLeft, left, center, right, farRight};
    }
#endif // SUMO3KG

// Definição de pinos para os robôs sumo mini
#ifdef SUMOMINI
    namespace motors
    {
        int leftMotor = 5;
        int rightMotor = 6;
    }
    namespace edgeSensors
    {
        int leftFrontEdge = 2;
        int rightFrontEdge = 4;
    }
    namespace opponentsSensors
    {
        int left = 12;
        int right = 13;

        int sensors[] = {left, right};
    }
#endif
}
#endif