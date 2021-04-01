#ifndef WEBOTS_SENSORS_HPP
#define WEBOTS_SENSORS_HPP
#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/DistanceSensor.hpp"
#include "../utilities/messages/messages.hpp"

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

bool edgeDetected = false;

bool isEdgeDetected() { return edgeDetected; }

void readEdgeSensors()
{
    // 0=borda | 1024=semBorda
    bool left_edge = leftEdgeSensor->getValue() < 300;
    bool right_edge = rightEdgeSensor->getValue() < 300;
    if (left_edge || right_edge)
    {
        edgeDetected = true;
    }
    else
    {
        edgeDetected = false;
    }
}

// SENSORES DE OPONENTE
#define NUMBER_OF_OPPONENT_SENSORS 2
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-1, 1};
bool opponentSensorDetectionArray[NUMBER_OF_OPPONENT_SENSORS];
double _detectionError;
bool _opDetected = false;

bool isOpponentDetected() { return _opDetected; }

double getErrorFromOPSensors() { return _detectionError; };

int sumArray(bool vector[])
{
    int sum = 0;
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        sum += vector[index];
    }
    return sum;
}

void readOpponentSensors()
{
    // 0=semObjeto | 0(longe)->1060(perto)=objeto
    opponentSensorDetectionArray[0] = leftDistanceSensor->getValue() > 0.35;
    opponentSensorDetectionArray[1] = rightDistanceSensor->getValue() > 0.35;
    int buffer = sumArray(opponentSensorDetectionArray);
    if (buffer >= 1)
    {
        _opDetected = true;
    }
    else
    {
        _opDetected = false;
    }
}
#endif
