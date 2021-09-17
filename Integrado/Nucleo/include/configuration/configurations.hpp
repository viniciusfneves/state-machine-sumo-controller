#if !defined(CONFIGURATIONS_HPP)
#define CONFIGURATIONS_HPP

#include "../strategies/strategies.hpp"

// Status de execução das estratégias do robô
enum class RobotState{
    ready,
    starting,
    stopped,
    exec_initial,
    exec_search,
    exec_chase
};

struct Configurations
{
    // Define a velocidade máxima global do robô -> (int)[0, 255]
    int maxSpeed = 255;
    double radarSpeed = 1;
    // Define o tempo de acionamento do robô para a luta
    int startTime = 4000;
    // Guarda o estado atual do robô -> Inicializado com stopped
    RobotState robotState = RobotState::stopped;

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

// Muda o tempo de acionamento do robô para começar a luta
void setStartTime(int time)
{
    robotConfiguration.startTime = time;
}

// Muda na memória do robô o seu estado de execução atual
void changeRobotState(RobotState state){
    robotConfiguration.robotState = state;
}

// Altera a velocidade linear máxima global permitida para o robô
void changeMaxSpeed(int newSpeed){
    robotConfiguration.maxSpeed = newSpeed;
}

void changePIDSettings(double set_kp, double set_ki, double set_kd){
    robotConfiguration.Kp = set_kp;
    robotConfiguration.Ki = set_ki;
    robotConfiguration.Kd = set_kd;
}

#endif // CONFIGURATIONS_HPP
