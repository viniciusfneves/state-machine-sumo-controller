#ifndef EDGE_SENSOR_HPP
#define EDGE_SENSOR_HPP

#include "../../utilities/calculus/calculus.hpp"

#ifdef REAL_ROBOT
#include <pins/pins.hpp>
#define NUMBER_OF_EDGE_SENSORS 2

bool edgeSensorDetectionArray[NUMBER_OF_EDGE_SENSORS];

bool _edgeDetected = false;

bool isEdgeDetected() { return _edgeDetected; }

void readEdgeSensors()
{
    edgeSensorDetectionArray[0] = digitalRead(pins::edgeSensors::leftFrontEdge);
    edgeSensorDetectionArray[1] = digitalRead(pins::edgeSensors::rightFrontEdge);

    int reading = sumArray(edgeSensorDetectionArray, NUMBER_OF_EDGE_SENSORS);

    if (reading > 0)
    {
        _edgeDetected = true;
    }
    else
    {
        _edgeDetected = false;
    }
};

// Realiza as configurações necessárias para o sensoriamento de borda do robô
void initEdgeSensors()
{
    pinMode(pins::edgeSensors::leftFrontEdge, INPUT);
    pinMode(pins::edgeSensors::rightFrontEdge, INPUT);
};
#endif

#ifndef REAL_ROBOT
#include "../../webots/sensors.hpp"
#endif

#endif // EDGE_SENSOR_HPP