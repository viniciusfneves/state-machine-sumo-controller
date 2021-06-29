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
#ifdef SUMOMINI
    namespace motors
    {
        #ifndef ZE_PEQUENO
        int motorIn1 = 13;
        int motorIn2 = 14;
        #endif

        #ifdef ET_MINI
        int leftMotorIn1 = 14;
        int leftMotorIn2 = 13;
        int rightMotorIn1 = 10;
        int rightMotorIn2 = 09;
        #endif

        #ifdef MERI
        int leftMotorIn1 = 24;
        int leftMotorIn2 = 25;
        int rightMotorIn1 = 10;
        int rightMotorIn2 = 09;
        #endif
    }

    namespace edgeSensors
    {
        #ifdef ZE_PEQUENO
        int leftFrontEdge = 24;
        int rightFrontEdge = 25;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
        #endif
        
        #ifdef ET_MINI
        int leftFrontEdge = 01;
        int rightFrontEdge = 32;

        int sensors[] = {leftFrontEdge, rightFrontEdge};
        #endif
    }

    namespace opponentsSensors
    {
        #ifdef ZE_PEQUENO
        int rightFrontOpponent = 01;
        int leftFrontOpponent = 32;

        int sensors[] = {leftFrontOpponent, rightFrontOpponent};
        #endif

        #ifdef ET_MINI
        int leftFrontOpponent = 11;
        int centralFrontOpponent = 12;
        int rightFrontOpponent = 02;

        int sensor[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent}
        #endif

        #ifdef MERI
        int leftFrontOpponent = 03;
        int centralFrontOpponent = 04;
        int rightFrontOpponent = 05;
        int leftLatOpponent = 02;
        int rightLatOpponent = 08;

        int sensor[] = {leftFrontOpponent, centralFrontOpponent, rightFrontOpponent, leftLatOpponent, rightLatOpponent}
        #endif
    }

    namespace Debug
    {
        // Os RX, TX, SDA e SCL estão comentados pois 
        // não tinha certeza do uso
        
        #ifdef ZE_PEQUENO
        int led = 11;
        int start = 02;

        // int RX = 30;
        // int TX = 31;
        // int SDA = 27;
        // int SCL = 28;
        #endif

        #ifdef ET_MINI
        int led = 17; // define o LED?
        int reset = 29;
        int start = 25;

        // int RX = 30;
        // int TX = 31;
        // int SDA = 27;
        // int SCL = 28;
        #endif

        #ifdef MERI
        int ledConfig = 20;
        int ledCMD = 13;
        int batRead = 07;

        // int RX = 21;
        // int TX = 22;
        // int SDA = 26;
        // int SCL = 29;
        #endif
    }

#endif
}
#endif