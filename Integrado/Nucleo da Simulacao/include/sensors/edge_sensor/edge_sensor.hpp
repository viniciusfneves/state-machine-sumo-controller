#ifndef EDGE_SENSOR_HPP
#define EDGE_SENSOR_HPP

#ifdef REAL_ROBOT
#include <pins/pins.hpp>
#define NUMBER_OF_EDGE_SENSORS 2

bool edgeSensorDetectionArray[NUMBER_OF_EDGE_SENSORS];

bool _edgeDetected = false;

bool isEdgeDetected() { return _edgeDetected; }

void readEdgeSensors()
{
    edgeSensorDetectionArray[0] = digitalRead(pins::edgeSensors::leftEdge);
    edgeSensorDetectionArray[1] = digitalRead(pins::edgeSensors::rightEdge);
    if (edgeSensorDetectionArray[0] || edgeSensorDetectionArray[1])
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
    pinMode(pins::edgeSensors::leftEdge, INPUT);
    pinMode(pins::edgeSensors::rightEdge, INPUT);
};
#endif

#ifndef REAL_ROBOT
#include "../../webots/sensors.hpp"
#endif

#endif // EDGE_SENSOR_HPP