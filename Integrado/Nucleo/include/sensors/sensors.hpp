#if !defined(SENSORS_HPP)
#define SENSORS_HPP

#include "configuration/configurations.hpp"
#include "edge_sensor/edge_sensor.hpp"
#include "opponent_sensor/opponent_sensor.hpp"
#include "start_module/start_module.hpp"

void readSensors() {
    if (robotConfiguration.mode == Mode::Auto)
        readStartModule();
    readOpponentSensors();
    readEdgeSensors();
};

#endif  // SENSORS_HPP
