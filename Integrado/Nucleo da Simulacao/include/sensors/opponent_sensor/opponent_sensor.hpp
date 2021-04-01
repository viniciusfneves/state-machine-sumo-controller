#ifndef OPPONENT_SENSOR_HPP
#define OPPONENT_SENSOR_HPP

#include "../../utilities/calculus/calculus.hpp"

// SIMULAÇÃO
#ifndef REAL_ROBOT
#include "../../webots/sensors.hpp"
#endif

// SUMO 3KG
#ifdef SUMO3KG
#define NUMBER_OF_OPPONENT_SENSORS 5
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-2, -1, 0, 1, 2};
#endif

#ifdef SUMOMINI
#define NUMBER_OF_OPPONENT_SENSORS 2
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-1, 1};
#endif

// FUNÇÕES GLOBAIS - ARDUINO & ESP
#ifdef REAL_ROBOT
#include <pins/pins.hpp>

bool opponentSensorDetectionArray[NUMBER_OF_OPPONENT_SENSORS];

bool _opDetected = false;

double _detectionError;

bool isOpponentDetected() { return _opDetected; }

double getErrorFromOPSensors() { return _detectionError; };

void calculateError()
{
    double sum = 0.;
    double readings = 0.;
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        if (opponentSensorDetectionArray[index] == 1)
        {
            sum += opponentSensorWeight[index];
            readings += 1;
        }
    }
    _detectionError = sum / readings;
}

void readOpponentSensors()
{
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        opponentSensorDetectionArray[index] = digitalRead(pins::opponentsSensors::sensors[index]);
    }
    int reading = sumArray(opponentSensorDetectionArray, NUMBER_OF_OPPONENT_SENSORS);
    if (reading >= 1)
    {
        _opDetected = true;
    }
    else
    {
        _opDetected = false;
    }
    calculateError();
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