#ifndef EDGE_SENSOR_HPP
#define EDGE_SENSOR_HPP

#include "../../configuration/specifications.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../utilities/calculus/calculus.hpp"
#ifdef REAL_ROBOT
#include <pins/pins.hpp>

// Lê e atualiza as informações sobre as leituras dos sensores de borda do robô
// Atualiza o array de leitura e se a borda foi detectado ou não
void readEdgeSensors() {
    for (int index = 0; index < NUMBER_OF_EDGE_SENSORS; index++) {
        robotData.edgeSensorsDetectionArray[index] = digitalRead(pins::edgeSensors::sensors[index]);
    }

    robotData.edgeDetected = checkTrueOnArray(robotData.edgeSensorsDetectionArray, NUMBER_OF_EDGE_SENSORS);
};

// Realiza as configurações necessárias para o sensoriamento de borda do robô
void initEdgeSensors() {
    for (int edgePin : pins::edgeSensors::sensors) {
        pinMode(edgePin, INPUT);
    }
};
#endif

#ifdef WEBOTS
#include "../../webots/sensors.hpp"
#endif

#endif  // EDGE_SENSOR_HPP