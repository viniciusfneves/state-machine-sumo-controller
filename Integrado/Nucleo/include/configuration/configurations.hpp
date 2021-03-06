#if !defined(CONFIGURATIONS_HPP)
#define CONFIGURATIONS_HPP

#include "../strategies/strategies.hpp"

struct Configurations
{
    // Define a velocidade máxima global do robô -> (int)[0, 255]
    int maxSpeed = 255;

    double Kp = 1.7;
    double Ki = 0;
    double Kd = 0.6;

    // Define uma velocidade angular máxima para o modo de perseguição -> (double)[0,1]
    double maxAngularSpeedInChase = 0.55;

    // Define a inicialização padrão das estratégias
    InitialMove initialMove = InitialMove::full_frente;
    Search search = Search::radar;
    Chase chase = Chase::standard;
    Mode mode   = Mode::Auto;
};

// Objeto global de configurações do robô
Configurations robotConfiguration;

// strategy -> (enum) InitialMove
// Muda a configuração de estratégia de movimento inicial
void setInitialStrategy(InitialMove strategy)
{
    robotConfiguration.initialMove = strategy;
}

// strategy -> (enum) Search
// Muda a configuração de estratégia de busca
void setSearchStrategy(Search strategy)
{
    robotConfiguration.search = strategy;
}

// strategy -> (enum) Chase
// Muda a configuração de estratégia de perseguição
void setChaseStrategy(Chase strategy)
{
    robotConfiguration.chase = strategy;
}

// mode -> (enum) Mode
// Muda a configuração de modo de operação
void setMode(Mode mode)
{
    robotConfiguration.mode = mode;
}

#endif // CONFIGURATIONS_HPP
