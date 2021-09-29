#if !defined(SENSORS_HPP)
#define SENSORS_HPP

#include "edge_sensor/edge_sensor.hpp"
#include "opponent_sensor/opponent_sensor.hpp"
#ifdef ESP32_ENV
#include <communications/data/send_data.hpp>
#include <dynamic_data/dynamic_data.hpp>
#endif

void readSensors()
{
    readOpponentSensors();
    readEdgeSensors();
};

#endif // SENSORS_HPP
