#ifndef OPPONENT_SENSOR_HPP
#define OPPONENT_SENSOR_HPP

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
#include "../../pins/pins.hpp"

// VARIAVEIS GLOBAIS
bool opponentSensorDetectionArray[NUMBER_OF_OPPONENT_SENSORS];

double error;

int sumArray(bool vector[])
{
    int sum = 0;
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        sum += vector[index];
    }
    return sum;
};

int readOpponentSensors()
{
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        opponentSensorDetectionArray[index] = digitalRead(pins::opponentsSensors::sensors[index]);
    }
    return sumArray(opponentSensorDetectionArray);
};

// Realiza as configurações necessárias para a parte de sensoriamento de oponentes do robô
void initOpponentSensors()
{
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        pinMode(pins::opponentsSensors::sensors[index], INPUT);
    }
};
#endif

// MAIS FUNÇÕES GLOBAIS
double calculateError()
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
    return sum / readings;
}
bool isOpponentDetected()
{
    if (readOpponentSensors() >= 1)
    {
        error = calculateError();
        return true;
    }
    return false;
};

#endif // OPPONENT_SENSOR_HPP