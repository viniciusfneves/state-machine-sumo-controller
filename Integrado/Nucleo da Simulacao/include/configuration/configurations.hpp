#if !defined(CONFIGURATIONS_HPP)
#define CONFIGURATIONS_HPP

#include <string.h>
#include "../strategies/strategies.hpp"

struct Configurations
{
    // Define a velocidade máxima global do robô -> [0, 255]
    int maxSpeed = 255;

    double Kp = 60;
    double Ki = 0;
    double Kd = 0;

    // Define a inicialização padrão das estratégias
    InitialMove initialMove = InitialMove::none;
    Search search = Search::none;
    Chase chase = Chase::standard;
};

// Objeto global de configurações do robô
Configurations robotConfiguration;

// Muda a configuração de estratégia de movimento inicial
// (enum) InitialMove -> void
void setInitialStrategy(InitialMove strategy)
{
    robotConfiguration.initialMove = strategy;
};

// Muda a configuração de estratégia de busca
// (enum) Search -> void
void setSearchStrategy(Search strategy)
{
    robotConfiguration.search = strategy;
};

// Muda a configuração de estratégia de perseguição
// (enum) Chase -> void
void setChaseStrategy(Chase strategy)
{
    robotConfiguration.chase = strategy;
};

#endif // CONFIGURATION_OBJECT_HPP
