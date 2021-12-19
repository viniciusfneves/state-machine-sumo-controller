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
        const int leftMotorIN1 = 25;
        const int leftMotorIN2 = 25;
        const int rightMotorIN1 = 26;
        const int rightMotorIN2 = 26;
        const int servo = 27;
    }
    namespace edgeSensors
    {
        const int leftFrontEdge = 35;
        const int rightFrontEdge = 34;

        const int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        const int leftSide = 5;
        const int farLeft = 12;
        const int left = 33;
        const int center = 14;
        const int right = 15;
        const int farRight = 18;
        const int rightSide = 19;

        const int sensors[] = {farLeft, left, center, right, farRight};
    }
    const int startModule = 23;
#endif // VAL

#ifdef ATENA
    namespace motors
    {
        const int leftMotorIN1 = 25;
        const int leftMotorIN2 = 25;
        const int rightMotorIN1 = 26;
        const int rightMotorIN2 = 26;
        const int servo = 27;
    }
    namespace edgeSensors
    {
        const int leftFrontEdge = 35;
        const int rightFrontEdge = 34;

        const int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        const int leftSide = 5;
        const int farLeft = 12;
        const int left = 33;
        const int center = 14;
        const int right = 15;
        const int farRight = 18;
        const int rightSide = 19;

        const int sensors[] = {farLeft, left, center, right, farRight};
    }
#endif // ATENA

#ifdef APOLO
    namespace motors
    {
        const int leftMotor = 25;
        const int rightMotor = 26;
        const int servo = 27;
    }
    namespace edgeSensors
    {
        const int leftFrontEdge = 35;
        const int rightFrontEdge = 34;
        const int leftRearEdge = 39;
        const int rightRearEdge = 36;

        const int sensors[] = {leftFrontEdge, rightFrontEdge, leftRearEdge, rightRearEdge};
    }
    namespace opponentsSensors
    {
        const int leftSide = 5;
        const int farLeft = 12;
        const int left = 33;
        const int center = 14;
        const int right = 15;
        const int farRight = 18;
        const int rightSide = 19;

        const int sensors[] = {leftSide, farLeft, left, center, right, farRight, rightSide};
    }
#endif // APOLO

// Definição de pinos para os robôs sumo mini

    // MINIS //

#ifdef ZE_PEQUENO
    namespace motors
    {
        const int leftMotorIN1 = 10;
        const int leftMotorIN2 = 9;
        const int rightMotorIN1 = 6;
        const int rightMotorIN2 = 5;
    }
    namespace edgeSensors
    {
        const int leftFrontEdge = 15;
        const int rightFrontEdge = 16;

        const int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        const int rightFrontOpponent = 3;
        const int leftFrontOpponent = 2;

        const int sensors[] = {leftFrontOpponent, rightFrontOpponent};
    }
    namespace configuration
    {
        const int led = 7;
        const int start = 4;
        const int XHUT = 8;
    }
#endif

#ifdef ET_MINI
    namespace motors
    {
        const int leftMotorIN1 = 10;
        const int leftMotorIN2 = 9;
        const int rightMotorIN1 = 6;
        const int rightMotorIN2 = 5;
    }
    namespace edgeSensors
    {
        const int leftFrontEdge = 3;
        const int rightFrontEdge = 2;

        const int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        const int leftFrontOpponent = 7;
        const int centralFrontOpponent = 8;
        const int rightFrontOpponent = 4;

        const int sensors[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent};
    }
    namespace configuration
    {
        const int led = 13;
        const int start = 16;
        const int XHUT = 17;
    }
#endif

#ifdef MERI
    namespace motors
    {
        const int leftMotorIN1 = 18;
        const int leftMotorIN2 = 29;
        const int rightMotorIN1 = 27;
        const int rightMotorIN2 = 26;
    }
    namespace edgeSensors
    {
        const int leftFrontEdge = 3;
        const int rightFrontEdge = 2;

        const int sensors[] = {leftFrontEdge, rightFrontEdge};
    }
    namespace opponentsSensors
    {
        const int leftFrontOpponent = 39;
        const int centralFrontOpponent = 34;
        const int rightFrontOpponent = 35;
        const int leftLatOpponent = 36;
        const int rightLatOpponent = 25;

        const int sensors[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent, leftLatOpponent, rightLatOpponent};
    }
    namespace configuration
    {
        const int ledConfig = 4;
        const int ledCMD = 13;
        const int batRead = 33;
    }
#endif
}
#endif