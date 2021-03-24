#ifndef MOTORS_HPP
#define MOTORS_HPP

#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/Motor.hpp"
#define MAX_SPEED 250
#define MAX_PWM   255

using namespace webots;

Motor *leftMotor;
Motor *rightMotor;

double map(int x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int constrain(int input, int minimumValue, int maximumValue)
{
    if (input >= maximumValue)
        return maximumValue;
    if (input <= minimumValue)
        return minimumValue;
    return input;
}

double convertPWMinSpeed(int pwm)
{
    return map(pwm, -MAX_PWM, MAX_PWM, -MAX_SPEED, MAX_SPEED);
}

void driveMotors(int leftPWM, int rightPWM)
{
    leftPWM = constrain(leftPWM, -MAX_PWM, MAX_PWM);
    rightPWM = constrain(rightPWM, -MAX_PWM, MAX_PWM);
    int leftSpeed = convertPWMinSpeed(leftPWM);
    int rightSpeed = convertPWMinSpeed(rightPWM);
    leftMotor->setVelocity(leftSpeed);
    rightMotor->setVelocity(rightSpeed);
}

void stopMotors()
{
    leftMotor->setVelocity(0);
    rightMotor->setVelocity(0);
}

// Movimenta o robô baseado nos parâmetros de entrada de velocidade linear e velocidade angular desejada
// double linearSpeed -> Velocidade linear do robô -> Range [-1,1]
// double angularSpeed -> Velocidade angular do robô -> Range [-1,1]
void driveRobot(int linearSpeed, int angularSpeed)
{
    // Limita os parâmetros de entrada aos permitidos pela função
    // Só funciona se os parametros forem de -1 à 1, caso contrário utilize um MAP para definir as velocidas linear e angular
    linearSpeed = constrain(linearSpeed, -1, 1) * robotSpecifications.maxLinearSpeed;
    angularSpeed = constrain(angularSpeed, -1, 1) * robotSpecifications.maxAngularSpeed;

    // Transforma os parâmetros de velocidade linear e angular em potência para os motores
    int PWM_left = (2 * linearSpeed - angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius)) * 255;
    int PWM_right = (2 * linearSpeed + angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius)) * 255;

    //Assegura que a velocidade angular vai ser exercida como pedido, podendo alterar a velocidade linear para isso
    double maxSpeed = (PWM_left > PWM_right) ? PWM_left : PWM_right;
    double minSpeed = (PWM_left < PWM_right) ? PWM_left : PWM_right;

    if (maxSpeed > robotConfiguration.maxSpeed)
    {
        PWM_left -= maxSpeed - robotConfiguration.maxSpeed;
        PWM_right -= maxSpeed - robotConfiguration.maxSpeed;
    }
    else if (minSpeed < -robotConfiguration.maxSpeed)
    {
        PWM_left -= minSpeed + robotConfiguration.maxSpeed;
        PWM_right -= minSpeed + robotConfiguration.maxSpeed;
    }

    // Comanda os motores à rodar com as potências calculadas
    driveMotors(PWM_left, PWM_right);
};

Motor *initMotor(Robot *robot, char *motorName)
{
    Motor *motor = robot->getMotor(motorName);
    motor->setPosition(INFINITY);
    motor->setVelocity(0);
    return motor;
}

void initMotors(Robot *robot)
{
    leftMotor = initMotor(robot, (char *)"left wheel motor");
    rightMotor = initMotor(robot, (char *)"right wheel motor");
}

#endif
