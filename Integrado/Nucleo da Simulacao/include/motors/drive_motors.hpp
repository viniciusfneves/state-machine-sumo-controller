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
void drive(int PWM_esq, int PWM_dir)
{
#ifdef REAL_ROBOT
    analogWrite(pins::leftMotor, PWM_esq);
    analogWrite(pins::rightMotor, PWM_dir);
#endif
};

// Para toda a locomoção do robô
void stop()
{
#ifdef REAL_ROBOT
    analogWrite(pins::leftMotor, 0);
    analogWrite(pins::rightMotor, 0);
#endif
};

#endif