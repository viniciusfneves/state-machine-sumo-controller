#pragma once

#include <Arduino.h> //Todo arquivo que importar pins, terá Arduino.h como dependencia automaticamente

namespace pins
{
// Definição de pinos para os robôs sumo 3Kg

    // 3KG //

#ifdef VAL
    namespace motors
    {
        const int leftIN1 = 25;
        const int leftIN2 = 27;
        const int rightIN1 = 26;
        const int rightIN2 = 32;
    }
    namespace edgeSensors
    {
        const int left = 35;
        const int right = 34;

        const int sensors[] = {left, right};
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
        const int leftIN1 = 25;
        const int leftIN2 = 25;
        const int rightIN1 = 26;
        const int rightIN2 = 26;
    }
    namespace edgeSensors
    {
        const int left = 35;
        const int right = 34;

        const int sensors[] = {left, right};
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
#endif // ATENA

#ifdef APOLO
    namespace motors
    {
        const int left = 25;
        const int right = 26;
    }
    namespace edgeSensors
    {
        const int frontLeft = 35;
        const int rearLeft = 39;
        const int frontRight = 34;
        const int rearRight = 36;

        const int sensors[] = {frontLeft, frontRight};
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
    const int startModule = 23;
#endif // APOLO

// Definição de pinos para os robôs sumo mini

    // MINIS //

#ifdef ZE_PEQUENO
    namespace motors
    {
        const int leftIN1 = 10;
        const int leftIN2 = 9;
        const int rightIN1 = 6;
        const int rightIN2 = 5;
    }
    namespace edgeSensors
    {
        const int left = 15;
        const int right = 16;

        const int sensors[] = {left, right};
    }
    namespace opponentsSensors
    {
        const int right = 3;
        const int left = 2;

        const int sensors[] = {left, right};
    }
    namespace configuration
    {
        const int led = 7;
        const int XHUT = 8;
    }
    const int startModule = 23;
#endif

#ifdef ET_MINI
    namespace motors
    {
        const int leftIN1 = 10;
        const int leftIN2 = 9;
        const int rightIN1 = 6;
        const int rightIN2 = 5;
    }
    namespace edgeSensors
    {
        const int left = 3;
        const int right = 2;

        const int sensors[] = {left, right};
    }
    namespace opponentsSensors
    {
        const int left = 7;
        const int center = 8;
        const int right = 4;

        const int sensors[] = {left, center, right};
    }
    namespace configuration
    {
        const int led = 13;
        const int XHUT = 17;
    }
    const int startModule = 23;
#endif

#ifdef MERI
    namespace motors
    {
        const int leftIN1 = 18;
        const int leftIN2 = 29;
        const int rightIN1 = 27;
        const int rightIN2 = 26;
    }
    namespace edgeSensors
    {
        const int left = 3;
        const int right = 2;

        const int sensors[] = {left, right};
    }
    namespace opponentsSensors
    {
        const int leftLat = 36;
        const int left= 39;
        const int center = 34;
        const int right = 35;
        const int rightLat = 25;

        const int sensors[] = {leftLat, left, center, right, rightLat};
    }
    namespace configuration
    {
        const int ledConfig = 4;
        const int ledCMD = 13;
        const int batRead = 33;
    }
    const int startModule = 23;
#endif
}