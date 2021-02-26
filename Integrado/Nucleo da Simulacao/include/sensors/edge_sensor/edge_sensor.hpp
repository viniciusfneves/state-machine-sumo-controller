#ifndef EDGE_SENSOR_HPP
#define EDGE_SENSOR_HPP

#ifdef REAL_ROBOT
#include "../../pins/pins.hpp"

bool getLeftEdgeSensor() { return digitalRead(pins::leftEdge); };
bool getRightEdgeSensor() { return digitalRead(pins::rightEdge); };
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

#endif // BORDER_SENSOR_HPP