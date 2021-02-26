#ifndef EDGE_SENSOR_HPP
#define EDGE_SENSOR_HPP

#ifdef REAL_ROBOT
#include "../../pins/pins.hpp"

bool getLeftEdgeSensor() { return digitalRead(pins::edgeSensors::leftEdge); };
bool getRightEdgeSensor() { return digitalRead(pins::edgeSensors::rightEdge); };
#endif

#ifndef REAL_ROBOT
#include "../../webots/sensors.hpp"
#endif

bool isOnEdge()
{
    bool left_edge = getLeftEdgeSensor();
    bool right_edge = getRightEdgeSensor();
    if (left_edge || right_edge)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif // EDGE_SENSOR_HPP