#pragma once

#include <Arduino.h>  //-Todo arquivo que importar pins, terá Arduino.h como dependencia automaticamente

#include <map>

namespace pins {
    // ! 3KG //

#if defined(VAL) || (ATENA)
    namespace motors {
        const int leftIN1  = 25;
        const int leftIN2  = 27;
        const int rightIN1 = 26;
        const int rightIN2 = 32;
        const int left     = 25;
        const int right    = 26;
    }  // namespace motors
    namespace edgeSensors {
        const std::map<String, int> sensors = {
            {"frontLeft", 35},
            {"frontRight", 34},
            //{"rearLeft", 39},
            //{"rearRight", 36},
        };
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const std::map<String, int> sensors = {
            //{"leftSide", 5},
            {"farLeft", 12},
            {"left", 33},
            {"center", 14},
            {"right", 15},
            {"farRight", 18},
            //{"rightSide", 19},
        };
    }  // namespace opponentsSensors
    const int startModule = 23;
#endif  // VAL & ATENA

#ifdef APOLO
    namespace motors {
        const int leftIN1  = 25;
        const int leftIN2  = 27;
        const int rightIN1 = 26;
        const int rightIN2 = 32;
        const int left     = 25;
        const int right    = 26;
    }  // namespace motors
    namespace edgeSensors {
        const std::map<String, int> sensors = {
            {"frontLeft", 35},
            {"frontRight", 34},
            {"rearLeft", 39},
            {"rearRight", 36},
        };
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const std::map<String, int> sensors = {
            {"leftSide", 5},
            {"farLeft", 12},
            {"left", 33},
            {"center", 14},
            {"right", 15},
            {"farRight", 18},
            {"rightSide", 19},
        };
    }  // namespace opponentsSensors
    const int startModule = 23;
#endif  // APOLO

    // Definição de pinos para os robôs sumo mini

    // ! MINIS //

#if defined (ZE_PEQUENO) || (ET_MINI)
    namespace motors {
        const int leftIN1  = 18;
        const int leftIN2  = 19;
        const int rightIN1 = 17;
        const int rightIN2 = 16;
    }  // namespace motors
    namespace edgeSensors {
        const std::map<String, int> sensors = {
            //{"frontLeft", 27},
            //{"frontRight", 32},
        };

    }  // namespace edgeSensors
    namespace opponentsSensors {
        const std::map<String, int> sensors = {
            {"left", 23},
            //{"center", 25},
            {"right", 26},
        };

    }  // namespace opponentsSensors
    namespace configuration {
        const int led  = 4;
    }  // namespace configuration
    const int startModule = 5;
    const int XHUT        = 33;
#endif

#ifdef MERI
    namespace motors {
        const int leftIN1  = 18;
        const int leftIN2  = 19;
        const int rightIN1 = 27;
        const int rightIN2 = 26;
    }  // namespace motors
    namespace edgeSensors {
        const std::map<String, int> sensors = {
            //{"frontLeft", },
            //{"frontCenter", 16},
            //{"frontRight", 17},
        };
    }  // namespace edgeSensors
    namespace opponentsSensors {
        const std::map<String, int> sensors = {
            //{"farLeft", 36},
            {"left", 39},
            //{"center", 34},
            {"right", 35},
            //{"farRight", 25},
        };
    }  // namespace opponentsSensors
    namespace configuration {
        const int ledConfig = 4;
        const int ledCMD    = 13;
        const int batRead   = 33;
    }  // namespace configuration
    const int startModule = 23;
#endif
}  // namespace pins
