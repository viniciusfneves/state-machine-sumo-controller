#ifndef _MAIN_
#define _MAIN_

//#define ARDUINO   // Comente essa linha para rodar o código simulando no Webots
#define WEBOTS // Comente essa linha para rodar o código no Arduino

// ------------------------------
// PRÉ-DEFINIÇÕES DOS AMBIENTES
// ------------------------------
// Pré-definições Gerais
#include "../include/event_handler/event_handler.hpp"
// Pré-definições do Arduino
#ifdef ARDUINO
#include <Arduino.h>
#endif
// Pré-definições do Webots
#ifdef WEBOTS
#include "C:/Program Files/Webots/include/controller/cpp/webots/Robot.hpp"
#include "C:/Program Files/Webots/include/controller/cpp/webots/Motor.hpp"
#include "../motors/motors.hpp"

using namespace webots;

// Criação da instancia do robô
Robot *robot = new Robot();
// Criação das instancias dos motores
Motor *leftMotor = initMotor(robot, (char *)"left wheel motor");
Motor *rightMotor = initMotor(robot, (char *)"right wheel motor");
#endif
// Fim das Pré-definições dos Ambientes

// ------------------------------
// VARIÁVEIS GLOBAIS DOS AMBIENTES
// ------------------------------
double value;
// Fim das variáveis globais dos ambientes

// Inicialização das lógicas compartilhadas entre o Arduino e o Webots
void initCode()
{
    value = 0.9; // Porcentagem de tempo do LED aceso (Arduino) ou da velocidade do robô (Webots)
}

// Função que deve ser chamada tanto no loop do Webots quanto no "void loop()" do Arduino
// Aqui que devem ocorrer os chamamentos do resto do código
void loopCode()
{
#ifdef ARDUINO
    handle_events();
#endif

#ifdef WEBOTS
    handle_events();
#endif
}

#endif