#pragma once

#include "../strategies/strategies.hpp"

struct Configurations {
    // Define a velocidade máxima global do robô -> (int)[0, 255]
    int maxSpeed = 255;

    // Parâmetros para a estratégia de radar -> (double)[-1, 1]
    double radarSpeed = 1;

    // Parâmetros para as estratégias de Arco
    double arcAgularSpeed = 0.25;
    int    angle          = 0;
    int    arcTimeout     = 750;

    // Define uma velocidade angular máxima para o modo de perseguição -> (double)[0,1]
    double maxAngularSpeedInChase = 0.595;

    // Parâmetros de ajuste para a função rotateRobot
    double angleBias = 550;
    double speedBias = 0.25;

    // Define o tempo de acionamento do robô para a luta
    int startTime = 0;

    // Parâmetros do PID
    double Kp = 0.195;
    double Ki = 0.023;
    double Kd = 0.081;

    // Define a inicialização padrão das estratégias
    InitialMove initialMove = InitialMove::full_frente;
    Search      search      = Search::radar;
    Chase       chase       = Chase::standard;
    Mode        mode        = Mode::Auto;
};

// Objeto global de configurações do robô
Configurations robotConfiguration;
