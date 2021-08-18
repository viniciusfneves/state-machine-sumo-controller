#ifndef WEBOTS_SENSORS_HPP
#define WEBOTS_SENSORS_HPP
#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/DistanceSensor.hpp"
#include "../dynamic_data/dynamic_data.hpp"
#include "../utilities/calculus/calculus.hpp"

using namespace webots;

int timeStep = 0;

DistanceSensor *leftEdgeSensor;
DistanceSensor *rightEdgeSensor;
DistanceSensor *leftDistanceSensor;
DistanceSensor *rightDistanceSensor;

// FUNÇÕES GERAIS
void enableSensors()
{
    leftEdgeSensor->enable(timeStep);
    rightEdgeSensor->enable(timeStep);
    leftDistanceSensor->enable(timeStep);
    rightDistanceSensor->enable(timeStep);
}

// void disableSensors()
// {
//     leftEdgeSensor->disable();
//     rightEdgeSensor->disable();
//     leftDistanceSensor->disable();
//     rightDistanceSensor->disable();
// }

void initSensors(Robot *robot, int _timeStep)
{
    timeStep = _timeStep;

    // Criando instancia dos sensores
    rightEdgeSensor = robot->getDistanceSensor("edge right");
    leftEdgeSensor = robot->getDistanceSensor("edge left");
    rightDistanceSensor = robot->getDistanceSensor("opponent right");
    leftDistanceSensor = robot->getDistanceSensor("opponent left");

    // Habilitando os sensores
    enableSensors();
}

// SENSORES DE BORDA

void readEdgeSensors()
{
    // 0=borda | 1024=semBorda
    robotData.edgeSensorsDetectionArray[0] = leftEdgeSensor->getValue() < 300;
    robotData.edgeSensorsDetectionArray[1] = rightEdgeSensor->getValue() < 300;
    robotData.edgeDetected = checkTrueOnArray(robotData.edgeSensorsDetectionArray, 2);
}

// SENSORES DE OPONENTE
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-1, 1};

void readOpponentSensors()
{
    // 0=semObjeto | 0(longe)->1060(perto)=objeto
    robotData.opponentSensorsDetectionArray[0] = leftDistanceSensor->getValue() > 0.35;
    robotData.opponentSensorsDetectionArray[1] = rightDistanceSensor->getValue() > 0.35;

    robotData.opDetected = checkTrueOnArray(robotData.opponentSensorsDetectionArray, NUMBER_OF_OPPONENT_SENSORS);
    if (isOpponentDetected())
    {
        robotData.opError = calculateError(robotData.opponentSensorsDetectionArray, opponentSensorWeight, NUMBER_OF_OPPONENT_SENSORS);
    }
}
#endif
