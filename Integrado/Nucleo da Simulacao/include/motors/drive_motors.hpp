#ifndef DRIVE_MOTORS_HPP
#define DRIVE_MOTORS_HPP

// Adiciona a função analogWrite para compilação com ESP32
#ifdef SUMO3KG
#include <analogWrite.h>
#endif

// No caso de simulação, importa a biblioteca com as funções de
// locomoção do WeBots
#ifndef REAL_ROBOT
#include "../webots/motors.hpp"
#endif

// Dependências gerais
#include "../pins/pins.hpp"

// Envia sinais PWM para as portas dos motores ESQ e DIR
void drive(int PWM_left, int PWM_right)
{
#ifdef REAL_ROBOT
    analogWrite(pins::leftMotor, PWM_left);
    analogWrite(pins::rightMotor, PWM_right);
#endif
#ifndef REAL_ROBOT
    move(PWM_left, PWM_right);
#endif
};

// Para toda a locomoção do robô
void stop()
{
#ifdef REAL_ROBOT
    analogWrite(pins::leftMotor, 0);
    analogWrite(pins::rightMotor, 0);
#endif
#ifndef REAL_ROBOT
    move(0, 0);
#endif
};

#endif