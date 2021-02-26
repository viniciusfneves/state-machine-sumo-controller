#ifndef OPPONENT_SENSOR_HPP
#define OPPONENT_SENSOR_HPP

#ifdef REAL_ROBOT
bool getLeftOpponentSensor(){};
bool getRightOpponentSensor(){};
#endif

#ifndef REAL_ROBOT
#include "../../webots/sensors.hpp"
#endif

#endif // OPPONENT_SENSOR_HPP