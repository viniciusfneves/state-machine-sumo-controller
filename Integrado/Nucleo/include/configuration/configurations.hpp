#if !defined(CONFIGURATIONS_HPP)
#define CONFIGURATIONS_HPP

#include "../event_handler/circular_buffer.hpp"
#include "../strategies/strategies.hpp"

struct Configurations {
    // Define a velocidade máxima global do robô -> (int)[0, 255]
    int maxSpeed = 255;
    double radarSpeed = 1;
    // Define as velocidades lineares e angulares das estratégias iniciais de arco (0 a 1)
    double archLinearVelocity = 1;
    double longArchAngularVelocity = 0.5;
    double shortArchAngularVelocity = 0.7;

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

// strategy -> (enum) InitialMove
// Muda a configuração de estratégia de movimento inicial
void setInitialStrategy(InitialMove strategy) {
    robotConfiguration.initialMove = strategy;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

// strategy -> (enum) Search
// Muda a configuração de estratégia de busca
void setSearchStrategy(Search strategy) {
    robotConfiguration.search = strategy;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

// strategy -> (enum) Chase
// Muda a configuração de estratégia de perseguição
void setChaseStrategy(Chase strategy) {
    robotConfiguration.chase = strategy;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

// mode -> (enum) Mode
// Muda a configuração de modo de operação
void setMode(Mode mode) {
    robotConfiguration.mode = mode;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

// Muda o tempo de acionamento do robô para começar a luta
void setStartTime(int time) {
    robotConfiguration.startTime = time;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

// Altera a velocidade linear máxima global permitida para o robô
void setMaxSpeed(int newSpeed) {
    robotConfiguration.maxSpeed = newSpeed;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

// Altera os parâmetros para cálculo do controle PID
void changePIDSettings(double set_kp, double set_ki, double set_kd) {
    robotConfiguration.Kp = set_kp;
    robotConfiguration.Ki = set_ki;
    robotConfiguration.Kd = set_kd;
    addEventToQueue(Event::BroadcastRobotConfiguration);
}

#endif  // CONFIGURATIONS_HPP
