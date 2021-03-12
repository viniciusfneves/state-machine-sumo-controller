#ifndef DRIVE_MOTORS_HPP
#define DRIVE_MOTORS_HPP

#ifdef REAL_ROBOT

// Dependências gerais
#include <pins/pins.hpp>

// Adiciona a função analogWrite para compilação com ESP32
#ifdef SUMO3KG
#include <analogWrite.h>
#endif

// Envia sinais PWM para as portas dos motores ESQ e DIR
void drive(int PWM_left, int PWM_right)
{
    PWM_left = constrain(PWM_left, -255, 255);
    PWM_right = constrain(PWM_right, -255, 255);
    analogWrite(pins::motors::leftMotor, PWM_left);
    analogWrite(pins::motors::rightMotor, PWM_right);
};

// Para toda a locomoção do robô
void stop()
{
    analogWrite(pins::motors::leftMotor, 0);
    analogWrite(pins::motors::rightMotor, 0);
};

// Realiza as configurações necessárias para a parte de locomoção do robô
void initMotors()
{
#ifdef SUMO3KG
    // Define a resolução de saída dos pinos de PWM do ESP32
    analogWriteResolution(pins::motors::leftMotor, 12);
    analogWriteResolution(pins::motors::rightMotor, 12);
#endif
    pinMode(pins::motors::leftMotor, OUTPUT);
    pinMode(pins::motors::rightMotor, OUTPUT);
    analogWrite(pins::motors::leftMotor, 0);
    analogWrite(pins::motors::rightMotor, 0);
}

#endif //ifdef REAL_ROBOT

// No caso de simulação, importa a biblioteca com as funções de locomoção do WeBots
#ifndef REAL_ROBOT
#include "../webots/motors.hpp"
#endif

#endif //DRIVE_MOTORS_HPP