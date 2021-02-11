#ifndef ACTIONS_HPP
    #define ACTIONS_HPP

    #include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
    #include "C:/Program Files/Webots/include/controller/cpp/webots/Motor.hpp"
    #include "../../../Simulacao/controllers/main/lib/motors/motors.hpp"

    using namespace webots;

    // Criação da instancia do robô
    Robot *robot = new Robot();
    // Criação das instancias dos motores
    Motor *leftMotor = initMotor(robot, (char *)"left wheel motor");
    Motor *rightMotor = initMotor(robot, (char *)"right wheel motor");

/*
    void locomotion(Motor *leftMotor, double leftValue, Motor *rightMotor, double rightValue) {
        move(leftMotor, leftValue, rightMotor, rightValue);
    }*/

    // auto exemplo = []{};

    auto run = [] {
        move(rightMotor, 1, leftMotor, 1);
    };

#endif