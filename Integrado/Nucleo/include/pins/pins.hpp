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

        int sensors[] = {leftFrontEdge, rightFrontEdge, leftRearEdge, rightRearEdge};
    }
    namespace opponentsSensors
    {
        int leftSide = 5;
        int farLeft = 12;
        int left = 33;
        int center = 14;
        int right = 15;
        int farRight = 18;
        int rightSide = 19;

        int sensors[] = {farLeft, left, center, right, farRight};
    }
#endif // SUMO3KG

// Definição de pinos para os robôs sumo mini
#ifdef ZE_PEQUENO
    namespace motors{
        int motorIn1 = 9;
        int motorIn2 = 10;
    }
    namespace edgeSensors{
        int leftFrontEdge = 15;
        int rightFrontEdge = 16;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors{
        int rightFrontOpponent = 03;
        int leftFrontOpponent = 02;

        int sensors[] = {leftFrontOpponent, rightFrontOpponent};
    }
    namespace configuration{
        int led = 07;
        int start = 04;
        int XHUT = 08;
    }
#endif

#ifdef ET_MINI
    namespace motors{
        int leftMotorIn1 = 10;
        int leftMotorIn2 = 09;
        int rightMotorIn1 = 06;
        int rightMotorIn2 = 05;
    }
    namespace edgeSensors{
        int leftFrontEdge = 03;
        int rightFrontEdge = 02;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors{
        int leftFrontOpponent = 07;
        int centralFrontOpponent = 08;
        int rightFrontOpponent = 04;

        int sensor[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent}
    }
    namespace configuration{
        int led = 13;
        int start = 16;
        int XHUT = 17;
    }
#endif

#ifdef MERI
    namespace motors{
        int leftMotorIn1 = 18;
        int leftMotorIn2 = 29;
        int rightMotorIn1 = 27;
        int rightMotorIn2 = 26;
    }
    namespace opponentsSensors{
        int leftFrontOpponent = 39;
        int centralFrontOpponent = 34;
        int rightFrontOpponent = 35;
        int leftLatOpponent = 36;
        int rightLatOpponent = 25;

        int sensor[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent, leftLatOpponent, rightLatOpponent}
    }
    namespace configuration{
        int ledConfig = 04;*
        int ledCMD = 13;*
        int batRead = 33;*
    }
#endif
}
#endif