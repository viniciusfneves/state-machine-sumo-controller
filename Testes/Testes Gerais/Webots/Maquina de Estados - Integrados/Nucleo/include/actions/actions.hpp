#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/Motor.hpp"
#include "../../../Webots/controllers/main/lib/motors/motors.hpp"
#include <windows.h>

using namespace webots;
using namespace std;
// Criação da instancia do robô
Robot *robot = new Robot();
// Criação das instancias dos motores
Motor *leftMotor = initMotor(robot, (char *)"left wheel motor");
Motor *rightMotor = initMotor(robot, (char *)"right wheel motor");

auto run = [] {
    move(rightMotor, 1, leftMotor, 1);
};

auto halt = []{
    move(rightMotor, 0, leftMotor, 0);
};

auto rotate_right = []{
    move(rightMotor, -0.6, leftMotor, 0.6);
};

auto rotate_left = []{
    move(rightMotor, 0.5, leftMotor, -0.5);
};

void sleepTime()
{
    cout << "Sleeping" << endl;
    Sleep(5000);
};
#endif