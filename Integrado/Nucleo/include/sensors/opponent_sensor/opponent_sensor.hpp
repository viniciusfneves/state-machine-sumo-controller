#pragma once

#include "../../configuration/specifications.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../utilities/calculus/calculus.hpp"

#ifdef WEBOTS
#include "../../webots/sensors.hpp"
#else
#include <pins/pins.hpp>
#endif

// SUMO 3KG
#if defined(VAL) || defined(ATENA)
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-2, -1, 0, 1, 2};
#endif

#ifdef APOLO
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-4, -2, -1, 0, 1, 2, 4};
#endif

// SUMO MINI
#if defined(ET_MINI) || defined(ZE_PEQUENO)
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-1, 1};
#endif

#ifdef MERI
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-3, -1, 0, 1, 3};
#endif

// Lê e atualiza as informações sobre as leituras dos sensores de oponente do robô
// Atualiza o array de leitura, se o oponente foi detectado ou não e o erro relacionado à detecção
void readOpponentSensors() {
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++) {
        robotData.opponentSensorsDetectionArray[index] = digitalRead(pins::opponentsSensors::sensors[index]);
    }

    robotData.opDetected = checkTrueOnArray(robotData.opponentSensorsDetectionArray, NUMBER_OF_OPPONENT_SENSORS);

    if (isOpponentDetected()) {
        robotData.opError = calculateError(robotData.opponentSensorsDetectionArray, opponentSensorWeight, NUMBER_OF_OPPONENT_SENSORS);
    }
}

// Realiza as configurações necessárias para a parte de sensoriamento de oponentes do robô
void initOpponentSensors() {
    for (int opPin : pins::opponentsSensors::sensors) {
        pinMode(opPin, INPUT);
    }
}
