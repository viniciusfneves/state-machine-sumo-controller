#ifndef SET_CONFIGURATION_HPP
#define SET_CONFIGURATION_HPP

#include <communications/data/robot_data_json_encoder.hpp>
#include <configuration/configurations.hpp>
#include <dynamic_data/controller_data.hpp>

// strategy -> (enum) InitialMove
// Muda a configuração de estratégia de movimento inicial
void setInitialStrategy(InitialMove strategy) {
    robotConfiguration.initialMove = strategy;
    broadcastRobotConfiguration();
}

// strategy -> (enum) Search
// Muda a configuração de estratégia de busca
void setSearchStrategy(Search strategy) {
    robotConfiguration.search = strategy;
    broadcastRobotConfiguration();
}

// strategy -> (enum) Chase
// Muda a configuração de estratégia de perseguição
void setChaseStrategy(Chase strategy) {
    robotConfiguration.chase = strategy;
    broadcastRobotConfiguration();
}

// mode -> (enum) Mode
// Muda a configuração de modo de operação
void setMode(Mode mode) {
    robotConfiguration.mode = mode;
    broadcastRobotConfiguration();
}

// Muda o tempo de acionamento do robô para começar a luta
void setStartTime(int time) {
    robotConfiguration.startTime = time;
    broadcastRobotConfiguration();
}

// Altera a velocidade linear máxima global permitida para o robô
void setMaxSpeed(int newSpeed) {
    robotConfiguration.maxSpeed = newSpeed;
    broadcastRobotConfiguration();
}

// Altera os parâmetros para cálculo do controle PID
void changePIDSettings(double set_kp, double set_ki, double set_kd) {
    robotConfiguration.Kp = set_kp;
    robotConfiguration.Ki = set_ki;
    robotConfiguration.Kd = set_kd;
    broadcastRobotConfiguration();
}

void setCtrlType(Commander comm) {
    controllerData.commander = comm;
    broadcastRobotConfiguration();
}

void setCtrlFilter(CommandFilter filter) {
    controllerData.filterSettings = filter;
    broadcastRobotConfiguration();
}

void setCtrlMapping(CommandMap map) {
    controllerData.mapSettings = map;
    broadcastRobotConfiguration();
}

#endif  // SET_CONFIGURATION_HPP