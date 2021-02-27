#ifndef SENSORS_HPP
#define SENSORS_HPP
#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/DistanceSensor.hpp"
#include "../utilities/messages/messages.hpp"

// DEFINES
#define NUMBER_OF_OPPONENT_SENSORS 2

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

int sumArray(bool vector[])
{
    int sum = 0;
    for (int index = 0; index < NUMBER_OF_OPPONENT_SENSORS; index++)
    {
        sum += vector[index];
    }
    return sum;
};

// SENSORES DE BORDA

// 0=borda | 1024=semBorda
bool getLeftEdgeSensor()
{
    double reading = leftEdgeSensor->getValue();
    return reading < 300;
}
bool getRightEdgeSensor()
{
    double reading = rightEdgeSensor->getValue();
    return reading < 300;
}

// SENSORES DE OPONENTE

bool opponentSensorDetectionArray[NUMBER_OF_OPPONENT_SENSORS];
int opponentSensorWeight[NUMBER_OF_OPPONENT_SENSORS] = {-1, 1};
double error;

// 0=semObjeto | 0(longe)->1060(perto)=objeto
bool getLeftOpponentSensor()
{
    return leftDistanceSensor->getValue() > 0.35;
}
bool getRightOpponentSensor()
{
    return rightDistanceSensor->getValue() > 0.35;
}
int readOpponentSensors()
{
    opponentSensorDetectionArray[0] = getLeftOpponentSensor();
    opponentSensorDetectionArray[1] = getRightOpponentSensor();
    return sumArray(opponentSensorDetectionArray);
};
#endif
