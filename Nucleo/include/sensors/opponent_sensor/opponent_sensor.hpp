#pragma once

#include "../../configuration/configurations.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../utilities/calculus/calculus.hpp"

#ifdef WEBOTS
#include "../../webots/sensors.hpp"
#else
#include <pins/pins.hpp>
#endif

// Lê e atualiza as informações sobre as leituras dos sensores de oponente do robô
// Atualiza o array de leitura, se o oponente foi detectado ou não e o erro relacionado à detecção
void readOpponentSensors() {
    for (auto sensor = pins::opponentsSensors::sensors.begin(); sensor != pins::opponentsSensors::sensors.end(); sensor++) {
        int reading = digitalRead(sensor->second);
        if (robotConfiguration.invertOpReading) {
            updateOpSensors(sensor->first, !reading);
        } else {
            updateOpSensors(sensor->first, reading);
        }
    }

    updateOpDetection(checkDetection(robotData.opponentSensorsDetectionArray));

    if (isOpponentDetected()) {
        updateOpError(calculateError(robotData.opponentSensorsDetectionArray, robotConfiguration.opponentSensorWeight));
    }
}

// Realiza as configurações necessárias para a parte de sensoriamento de oponentes do robô
void initOpponentSensors() {
    for (auto sensorPin = pins::opponentsSensors::sensors.begin(); sensorPin != pins::opponentsSensors::sensors.end(); sensorPin++) {
        pinMode(sensorPin->second, INPUT);
    }
}