#if !defined(CONFIGURATIONS_HPP)
#define CONFIGURATIONS_HPP

#include "../strategies/strategies.hpp"

struct Configurations
{
    // Define a velocidade máxima global do robô -> [0, 255]
    int maxSpeed = 255;

    double Kp = 1.7;
    double Ki = 0;
    double Kd = 0.6;

    double maxAngularSpeedInChase = 0.55;

    // Define a inicialização padrão das estratégias
    InitialMove initialMove = InitialMove::full_frente;
    Search search = Search::radar;
    Chase chase = Chase::standard;
    Mode mode   = Mode::Auto;
};

// Objeto global de configurações do robô
Configurations robotConfiguration;

// Muda a configuração de estratégia de movimento inicial
// strategy -> (enum) InitialMove
void setInitialStrategy(InitialMove strategy)
{
    robotConfiguration.initialMove = strategy;
}

// Muda a configuração de estratégia de busca
// strategy -> (enum) Search
void setSearchStrategy(Search strategy)
{
    robotConfiguration.search = strategy;
}

// Muda a configuração de estratégia de perseguição
// strategy -> (enum) Chase
void setChaseStrategy(Chase strategy)
{
    robotConfiguration.chase = strategy;
}

void setMode(Mode mode)
{
    robotConfiguration.mode = mode;
}

#endif // CONFIGURATION_OBJECT_HPP
