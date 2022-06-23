#pragma once
#include <map>

#include "../strategies/strategies.hpp"

struct Configurations {
    // ! :::--- CONFIGURAÇÕES GERAIS ---:::

    // * SENSORES DE OPONENTE
    std::map<String, double> opponentSensorWeight = {
        {"leftSide", -4},
        {"farLeft", -2},
        {"left", -1},
        {"center", 0},
        {"right", 1},
        {"farRight", 2},
        {"rightSide", 4},
    };
    bool invertOpReading   = false;
    bool invertAngularAxis = false;
    bool invertLeftWheel   = false;
    bool invertRightWheel  = false;

    // * SENSORES DE BORDA
    // Define qual o valor a partir da leitura de sinais analógicos
    // a borda é considerada como detectada [0, 4095]
    double edgeDetectionThreshold = 500;

    // * CALIBRAÇÃO DE FUNÇÕES
    // Parâmetros de ajuste da função rotateRobot
    double angleBias = 200;
    double speedBias = 1;

    // Parâmetros do PID
    double Kp = 0.195;
    double Ki = 0.023;
    double Kd = 0.081;

    // Define o tempo de acionamento do robô para a luta
    int startTime = 0;

    // Define a velocidade máxima global do robô -> (int)[0, 255]
    int    maxSpeed           = 255;
    double rcCtrlLinearSpeed  = 0.85;
    double rcCtrlAngularSpeed = 0.85;

    // Define uma velocidade angular máxima para o modo de perseguição -> (double)[0,1]
    double maxAngularSpeedInChase = 0.595;

    // ! :::--- PARÂMETROS DE ESTRATÉGIAS ---:::

    // Parâmetro para velocidade de rotação do radar -> (double)[-1, 1]
    double radarSpeed = 0.75;

    // Parâmetro para as estratégias de Full Frente
    int fullFrenteTimeout = 120;

    // Parâmetros para as estratégias de Arco
    double arcAgularSpeed = 0.125;
    int    angle          = 0;
    int    arcTimeout     = 240;

    // Define a inicialização padrão das estratégias
    InitialMove initialMove = InitialMove::full_frente;
    Search      search      = Search::radar;
    Chase       chase       = Chase::standard;
    Mode        mode        = Mode::Auto;
};

// Objeto global de configurações do robô
Configurations robotConfiguration;

SemaphoreHandle_t xConfigSemaphore = xSemaphoreCreateMutex();