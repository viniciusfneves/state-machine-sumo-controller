#ifndef DRIVE_MOTORS_HPP
#define DRIVE_MOTORS_HPP

#ifdef REAL_ROBOT

// Dependências gerais
#include "../pins/pins.hpp"

// Adiciona a função analogWrite para compilação com ESP32
#ifdef SUMO3KG
#include <analogWrite.h>
#endif

// Envia sinais PWM para as portas dos motores ESQ e DIR
void drive(int PWM_left, int PWM_right)
{
    analogWrite(pins::leftMotor, PWM_left);
    analogWrite(pins::rightMotor, PWM_right);
};

// Para toda a locomoção do robô
void stop()
{
    analogWrite(pins::leftMotor, 0);
    analogWrite(pins::rightMotor, 0);
};

#endif //ifdef REAL_ROBOT

// No caso de simulação, importa a biblioteca com as funções de
// locomoção do WeBots
#ifndef REAL_ROBOT
#include "../webots/motors.hpp"
#endif

#endif //DRIVE_MOTORS_HPP