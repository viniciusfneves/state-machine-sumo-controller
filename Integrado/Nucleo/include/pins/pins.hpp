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
        int motorIn1 = 13;
        int motorIn2 = 14;
    }
    namespace edgeSensors{
        int leftFrontEdge = 24;
        int rightFrontEdge = 25;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors{
        int rightFrontOpponent = 01;
        int leftFrontOpponent = 32;

        int sensors[] = {leftFrontOpponent, rightFrontOpponent};
    }
    namespace configuration{
        int led = 00;
        int start = 00;
        int XHUT = 00;
    }
#endif

#ifdef ET_MINI
    namespace motors{
        int leftMotorIn1 = 14;
        int leftMotorIn2 = 13;
        int rightMotorIn1 = 10;
        int rightMotorIn2 = 09;
    }
    namespace edgeSensors{
        int leftFrontEdge = 01;
        int rightFrontEdge = 32;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors{
        int leftFrontOpponent = 11;
        int centralFrontOpponent = 12;
        int rightFrontOpponent = 02;

        int sensor[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent}
    }
    namespace configuration{
        int led = 00;
        int start = 00;
        int XHUT = 00;
    }
#endif

#ifdef MERI
    namespace motors{
        int leftMotorIn1 = 24;
        int leftMotorIn2 = 25;
        int rightMotorIn1 = 10;
        int rightMotorIn2 = 09;
    }
    namespace opponentsSensors{
        int leftFrontOpponent = 03;
        int centralFrontOpponent = 04;
        int rightFrontOpponent = 05;
        int leftLatOpponent = 02;
        int rightLatOpponent = 08;

        int sensor[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent, leftLatOpponent, rightLatOpponent}
    }
    namespace configuration{
        int ledConfig = 20;
        int ledCMD = 13;
        int batRead = 07;
    }
#endif
}
#endif