#ifndef OPPONENT_SENSOR_HPP
#define OPPONENT_SENSOR_HPP

#include "../../utilities/calculus/calculus.hpp"
#include "../../dynamic_data/dynamic_data.hpp"
#include "../../configuration/specifications.hpp"

// SIMULAÇÃO
#ifdef WEBOTS
#include "../../webots/sensors.hpp"
#endif

// SUMO 3KG
#ifdef SUMO3KG
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-2, -1, 0, 1, 2};
#endif

#ifdef SUMOMINI
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-1, 1};
#endif

// FUNÇÕES GLOBAIS - ARDUINO & ESP
#ifdef REAL_ROBOT
#include <pins/pins.hpp>

// Lê e atualiza as informações sobre as leituras dos sensores de oponente do robô
// Atualiza o array de leitura, se o oponente foi detectado ou não e o erro relacionado à detecção
void readOpponentSensors()
{
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        robotData.opponentSensorDetectionArray[index] = digitalRead(pins::opponentsSensors::sensors[index]);
    }

    robotData.opDetected = checkTrueOnArray(robotData.opponentSensorDetectionArray, NUMBER_OF_OPPONENT_SENSORS);

    if (isOpponentDetected())
    {
        robotData.opError = calculateError(robotData.opponentSensorDetectionArray, opponentSensorWeight, NUMBER_OF_OPPONENT_SENSORS);
    }
}

// Realiza as configurações necessárias para a parte de sensoriamento de oponentes do robô
void initOpponentSensors()
{
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        pinMode(pins::opponentsSensors::sensors[index], INPUT);
    }
}
#endif

#endif // OPPONENT_SENSOR_HPP