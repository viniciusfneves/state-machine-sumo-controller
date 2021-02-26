#ifndef SENSORS_HPP
#define SENSORS_HPP
#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/DistanceSensor.hpp"
#include "../utilities/messages/messages.hpp"

using namespace webots;

DistanceSensor *leftEdgeSensor;
DistanceSensor *rightEdgeSensor;
DistanceSensor *leftDistanceSensor;
DistanceSensor *rightDistanceSensor;

int timeStep = 0;

// 0=borda | 1024=semBorda
bool getLeftEdgeSensor()
{
    double reading = leftEdgeSensor->getValue();
    if (reading <= 300)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool getRightEdgeSensor()
{
    double reading = rightEdgeSensor->getValue();
    if (reading <= 300)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 0=semObjeto | 0(longe)->1060(perto)=objeto
bool getLeftOpponentSensor()
{
    return leftDistanceSensor->getValue();
}
bool getRightOpponentSensor()
{
    return rightDistanceSensor->getValue();
}

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
    rightEdgeSensor = robot->getDistanceSensor("border right");
    leftEdgeSensor = robot->getDistanceSensor("border left");
    rightDistanceSensor = robot->getDistanceSensor("opponent right");
    leftDistanceSensor = robot->getDistanceSensor("opponent left");

    // Habilitando os sensores
    enableSensors();
}

#endif
