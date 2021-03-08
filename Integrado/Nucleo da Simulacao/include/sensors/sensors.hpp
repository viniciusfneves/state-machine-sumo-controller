#if !defined(SENSORS_HPP)
#define SENSORS_HPP

#include "edge_sensor/edge_sensor.hpp"
#include "opponent_sensor/opponent_sensor.hpp"
#ifdef SUMO3KG
#include <communications/dynamic_data/send_data.hpp>
#endif

void readSensors()
{
    readOpponentSensors();
    readEdgeSensors();
    #ifdef SUMO3KG
    broadcastOPReadings(opponentSensorDetectionArray);
    broadcastEdgeReadings(edgeSensorDetectionArray);
    #endif
};

#endif // SENSORS_HPP
