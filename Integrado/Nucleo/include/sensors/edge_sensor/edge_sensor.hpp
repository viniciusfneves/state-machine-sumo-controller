#ifndef EDGE_SENSOR_HPP
#define EDGE_SENSOR_HPP

#include "../../utilities/calculus/calculus.hpp"
#include "../../dynamic_data/dynamic_data.hpp"
#include "../../configuration/specifications.hpp"
#ifdef REAL_ROBOT
#include <pins/pins.hpp>

// Lê e atualiza as informações sobre as leituras dos sensores de borda do robô
// Atualiza o array de leitura e se a borda foi detectado ou não
void readEdgeSensors()
{
    for (int index = 0; index < NUMBER_OF_EDGE_SENSORS; index++)
    {
        robotData.edgeSensorDetectionArray[index] = digitalRead(pins::edgeSensors::sensors[index]);
    }

    robotData.edgeDetected = verifyArray(robotData.edgeSensorDetectionArray, NUMBER_OF_EDGE_SENSORS);
};

// Realiza as configurações necessárias para o sensoriamento de borda do robô
void initEdgeSensors()
{
    for (int index = 0; index < NUMBER_OF_EDGE_SENSORS; index++)
    {
        pinMode(pins::edgeSensors::sensors[index], INPUT);
    }
};
#endif

#ifdef WEBOTS
#include "../../webots/sensors.hpp"
#endif

#endif // EDGE_SENSOR_HPP