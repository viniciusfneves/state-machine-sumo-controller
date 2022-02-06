#pragma once

#include "../strategies/strategies.hpp"

struct Configurations {
    // Define a velocidade máxima global do robô -> (int)[0, 255]
    int maxSpeed = 255;
    double radarSpeed = 1;

    // Define o tempo de acionamento do robô para a luta
    int startTime = 25;

    // Parâmetros do PID
    double Kp = 1.7;
    double Ki = 0;
    double Kd = 0.6;

    // Define uma velocidade angular máxima para o modo de perseguição -> (double)[0,1]
    double maxAngularSpeedInChase = 0.55;

    // Define a inicialização padrão das estratégias
    InitialMove initialMove = InitialMove::full_frente;
    Search search = Search::radar;
    Chase chase = Chase::standard;
    Mode mode = Mode::Auto;
};

// Objeto global de configurações do robô
Configurations robotConfiguration;
