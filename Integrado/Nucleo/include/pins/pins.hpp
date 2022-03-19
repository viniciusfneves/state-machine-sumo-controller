#pragma once

#include <Arduino.h>  //-Todo arquivo que importar pins, terá Arduino.h como dependencia automaticamente

namespace pins {
    // Definição de pinos para os robôs sumo 3Kg

    // 3KG //

#ifdef VAL
    namespace motors {
        const int leftIN1  = 25;
        const int leftIN2  = 27;
        const int rightIN1 = 26;
        const int rightIN2 = 32;
        const int left  = 25;
        const int right = 26;
    }  // namespace motors
    namespace edgeSensors {
        const int left  = 35;
        const int right = 34;

        const int sensors[] = {left, right};
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const int leftSide  = 5;
        const int farLeft   = 12;
        const int left      = 33;
        const int center    = 14;
        const int right     = 15;
        const int farRight  = 18;
        const int rightSide = 19;

        const int sensors[] = {farLeft, left, center, right, farRight};
    }  // namespace opponentsSensors
    const int startModule = 23;
#endif  // VAL

#ifdef ATENA
    namespace motors {
        const int leftIN1  = 25;
        const int leftIN2  = 25;
        const int rightIN1 = 26;
        const int rightIN2 = 26;
    }  // namespace motors
    namespace edgeSensors {
        const int left  = 35;
        const int right = 34;

        const int sensors[] = {left, right};
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const int leftSide  = 5;
        const int farLeft   = 12;
        const int left      = 33;
        const int center    = 14;
        const int right     = 15;
        const int farRight  = 18;
        const int rightSide = 19;

        const int sensors[] = {farLeft, left, center, right, farRight};
    }  // namespace opponentsSensors
    const int startModule = 23;
#endif  // ATENA

#ifdef APOLO
    namespace motors {
        const int left  = 25;
        const int right = 26;
    }  // namespace motors
    namespace edgeSensors {
        const int frontLeft  = 35;
        const int rearLeft   = 39;
        const int frontRight = 34;
        const int rearRight  = 36;

        const int sensors[] = {frontLeft, frontRight};
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const int leftSide  = 5;
        const int farLeft   = 12;
        const int left      = 33;
        const int center    = 14;
        const int right     = 15;
        const int farRight  = 18;
        const int rightSide = 19;

        const int sensors[] = {leftSide, farLeft, left, center, right, farRight, rightSide};
    }  // namespace opponentsSensors
    const int startModule = 23;
#endif  // APOLO

    // Definição de pinos para os robôs sumo mini

    // MINIS //

#ifdef ZE_PEQUENO
    namespace motors {
        const int leftIN1  = 18;
        const int leftIN2  = 19;
        const int rightIN1 = 14;
        const int rightIN2 = 15;
    }  // namespace motors
    namespace edgeSensors {
        const int left  = 27;
        const int right = 32;

        const int sensors[] = {left, right};
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const int left   = 23;
        const int center = 25;
        const int right  = 26;

        const int sensors[] = {left, right};
    }  // namespace opponentsSensors
    namespace configuration {
        const int led  = 4;
        const int XHUT = 33;
    }  // namespace configuration
    const int startModule = 5;
#endif

#ifdef ET_MINI
    namespace motors {
        const int leftIN1  = 18;
        const int leftIN2  = 19;
        const int rightIN1 = 14;
        const int rightIN2 = 15;
    }  // namespace motors
    namespace edgeSensors {
        const int left  = 27;
        const int right = 32;

        const int sensors[] = {left, right};
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const int left   = 23;
        const int center = 25;
        const int right  = 26;

        const int sensors[] = {left, right};
    }  // namespace opponentsSensors
    namespace configuration {
        const int led  = 4;
        const int XHUT = 33;
    }  // namespace configuration
    const int startModule = 5;
#endif

#ifdef MERI
    namespace motors {
        const int leftIN1  = 18;
        const int leftIN2  = 29;
        const int rightIN1 = 27;
        const int rightIN2 = 26;
    }  // namespace motors
    namespace edgeSensors {
        const int left  = 3;
        const int right = 2;

        const int sensors[] = {left, right};
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const int leftLat  = 36;
        const int left     = 39;
        const int center   = 34;
        const int right    = 35;
        const int rightLat = 25;

        const int sensors[] = {leftLat, left, center, right, rightLat};
    }  // namespace opponentsSensors
    namespace configuration {
        const int ledConfig = 4;
        const int ledCMD    = 13;
        const int batRead   = 33;
    }  // namespace configuration
    const int startModule = 23;
#endif
}  // namespace pins