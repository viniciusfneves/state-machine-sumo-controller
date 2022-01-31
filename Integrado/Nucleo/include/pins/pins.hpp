#ifndef PINS_HPP
#define PINS_HPP
#include <Arduino.h> //Todo arquivo que importar pins, terá Arduino.h como dependencia automaticamente

namespace pins
{
// Definição de pinos para os robôs sumo 3Kg

    // 3KG //

#ifdef VAL
    namespace motors
    {
        int leftMotorIN1 = 25;
        int leftMotorIN2 = 25;
        int rightMotorIN1 = 26;
        int rightMotorIN2 = 26;
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
#endif // VAL

#ifdef ATENA
    namespace motors
    {
        int leftMotorIN1 = 25;
        int leftMotorIN2 = 25;
        int rightMotorIN1 = 26;
        int rightMotorIN2 = 26;
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
#endif // ATENA

#ifdef APOLO
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

        int sensors[] = {leftSide, farLeft, left, center, right, farRight, rightSide};
    }
#endif // APOLO

// Definição de pinos para os robôs sumo mini

    // MINIS //

#ifdef ZE_PEQUENO
    namespace motors
    {
        int leftMotorIN1 = 18;
        int leftMotorIN2 = 19;
        int rightMotorIN1 = 14;
        int rightMotorIN2 = 15;
    }
    namespace edgeSensors
    {
        int leftFrontEdge = 27;
        int rightFrontEdge = 32;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        int leftFrontOpponent = 23;
        int centralFrontOpponent = 25;
        int rightFrontOpponent = 26;

        int sensors[] = {leftFrontOpponent, rightFrontOpponent, centralFrontOpponent};
    }
    namespace configuration
    {
        int led = 4;
        int start = 5;
        int XHUT = 33;
    }
#endif

#ifdef ET_MINI
    namespace motors
    {
        int leftMotorIN1 = 18;
        int leftMotorIN2 = 19;
        int rightMotorIN1 = 14;
        int rightMotorIN2 = 15;
    }
    namespace edgeSensors
    {
        int leftFrontEdge = 27;
        int rightFrontEdge = 32;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        int leftFrontOpponent = 23;
        int centralFrontOpponent = 25;
        int rightFrontOpponent = 26;

        int sensors[] = {leftFrontOpponent, rightFrontOpponent, centralFrontOpponent};
    }
    namespace configuration
    {
        int led = 4;
        int start = 5;
        int XHUT = 33;
    }
#endif

#ifdef MERI
    namespace motors
    {
        int leftMotorIN1 = 18;
        int leftMotorIN2 = 29;
        int rightMotorIN1 = 27;
        int rightMotorIN2 = 26;
    }
    namespace edgeSensors
    {
        int leftFrontEdge = 3;
        int rightFrontEdge = 2;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        int leftFrontOpponent = 39;
        int centralFrontOpponent = 34;
        int rightFrontOpponent = 35;
        int leftLatOpponent = 36;
        int rightLatOpponent = 25;

        int sensors[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent, leftLatOpponent, rightLatOpponent};
    }
    namespace configuration
    {
        int ledConfig = 4;
        int ledCMD = 13;
        int batRead = 33;
    }
#endif
}
#endif