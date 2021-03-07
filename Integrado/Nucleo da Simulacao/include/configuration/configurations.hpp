#if !defined(CONFIGURATIONS_HPP)
#define CONFIGURATIONS_HPP

#include <string.h>
#include "../strategies/strategies.hpp"

struct Configuration
{
    #ifdef SUMO3KG
    String robot_name        = "Atena"; 
    #endif
    // Definindo inicialização padrão para as estratégias
    InitialMove initialMove = InitialMove::none;
    Search      search      = Search::none;
    Chase       chase       = Chase::standard;
};

// Objeto global de configurações do robô
Configuration robotConfiguration;

void setInitialStrategy(InitialMove strategy){
    robotConfiguration.initialMove = strategy;
};
void setSearchStrategy(Search strategy){
    robotConfiguration.search = strategy;
};
void setChaseStrategy(Chase strategy){
    robotConfiguration.chase = strategy;
};

#endif // CONFIGURATION_OBJECT_HPP
