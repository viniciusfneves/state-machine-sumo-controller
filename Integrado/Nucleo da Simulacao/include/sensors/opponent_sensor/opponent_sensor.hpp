#ifndef OPPONENT_SENSOR_HPP
#define OPPONENT_SENSOR_HPP

#define NUMBER_OF_SENSORS 5

bool opponentSensorDetectionArray[NUMBER_OF_SENSORS];

#ifdef REAL_ROBOT
#include "../../pins/pins.hpp"
#ifdef SUMO3KG
int opponentSensorWeight[5] = {-2, -1, 0, 1, 2};
#endif

int sumArray(bool vector[])
{
    int sum = 0;
    for (int index = 0; index < NUMBER_OF_SENSORS; index++)
    {
        sum += vector[index];
    }
    return sum;
};

int readOpponentSensors()
{
    for (int index = 0; index < NUMBER_OF_SENSORS; index++)
    {
        opponentSensorDetectionArray[index] = digitalRead(pins::opponentsSensors::sensors[index]);
    }
    return sumArray(opponentSensorDetectionArray);
};

bool isOpponentDetected()
{
    if (readOpponentSensors() >= 1)
    {
        return true;
    }
    return false;
};

void initOpponentSensors(){
    for (int index = 0; index < NUMBER_OF_SENSORS; index++){
        pinMode(pins::opponentsSensors::sensors[index], INPUT);
    }
};
#endif

#ifndef REAL_ROBOT
#include "../../webots/sensors.hpp"
#endif

#endif // OPPONENT_SENSOR_HPP