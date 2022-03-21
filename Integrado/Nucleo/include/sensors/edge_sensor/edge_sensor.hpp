#pragma once

#include "../../configuration/specifications.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../utilities/calculus/calculus.hpp"

#ifdef WEBOTS
#include "../../webots/sensors.hpp"
#else
#include <pins/pins.hpp>
#endif

// Lê e atualiza as informações sobre as leituras dos sensores de borda do robô
// Atualiza o array de leitura e se a borda foi detectado ou não
void readEdgeSensors() {
    for (auto sensor = pins::edgeSensors::sensors.begin(); sensor != pins::edgeSensors::sensors.end(); sensor++) {
        if (analogRead(sensor->second) < robotConfiguration.edgeDetectionThreshold) {
            updateEdgeSensors(sensor->first, true);
        } else {
            updateEdgeSensors(sensor->first, false);
        }
    }

    updateEdgeDetection(checkDetection(robotData.edgeSensorsDetectionArray));
};

// Realiza as configurações necessárias para o sensoriamento de borda do robô
void initEdgeSensors() {
    for (auto sensorPin = pins::edgeSensors::sensors.begin(); sensorPin != pins::edgeSensors::sensors.end(); sensorPin++) {
        pinMode(sensorPin->second, INPUT);
    }
};
