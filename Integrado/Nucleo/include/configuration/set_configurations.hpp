#pragma once

#include <communications/data/robot_data_json_encoder.hpp>
#include <configuration/configurations.hpp>
#include <dynamic_data/controller_data.hpp>

// mode -> (enum) Mode
// Muda a configuração de modo de operação
void setMode(Mode mode) {
    robotConfiguration.mode = mode;
    broadcastRobotConfiguration();
}

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

// Muda o tempo de acionamento do robô para começar a luta
void setStartTime(int time) {
    robotConfiguration.startTime = abs(time);
    broadcastRobotConfiguration();
}

// Altera a velocidade linear máxima global permitida para o robô
void setMaxSpeed(int newSpeed) {
    robotConfiguration.maxSpeed = abs(newSpeed);
    broadcastRobotConfiguration();
}
// Altera a velocidade linear máxima global permitida para o robô
void setRadarSpeed(double newSpeed) {
    robotConfiguration.radarSpeed = abs(newSpeed);
    broadcastRobotConfiguration();
}

void setMaxAngularSpeedInChase(double newSpeed) {
    robotConfiguration.maxAngularSpeedInChase = newSpeed;
    broadcastRobotConfiguration();
}

void setArcAngularSpeed(double newSpeed) {
    robotConfiguration.arcAgularSpeed = newSpeed;
    broadcastRobotConfiguration();
}

void setShortArcAngularSpeed(double newSpeed) {
    robotConfiguration.shortArcAgularSpeed = newSpeed;
    broadcastRobotConfiguration();
}

void setArcTimeout(int time) {
    robotConfiguration.arcTimeout = time;
    broadcastRobotConfiguration();
}

void setShortArcTimeout(int time) {
    robotConfiguration.shortArcTimeout = time;
    broadcastRobotConfiguration();
}

void setAngle(int newAngle) {
    robotConfiguration.angle = newAngle;
    broadcastRobotConfiguration();
}

void setRotateRobotAngleBias(double bias) {
    robotConfiguration.angleBias = bias;
    broadcastRobotConfiguration();
}

void setRotateRobotSpeedBias(double bias) {
    robotConfiguration.speedBias = abs(bias);
    broadcastRobotConfiguration();
}

// Altera os parâmetros para cálculo do controle PID
void changePIDSettings(double set_kp, double set_ki, double set_kd) {
    robotConfiguration.Kp = set_kp;
    robotConfiguration.Ki = set_ki;
    robotConfiguration.Kd = set_kd;
    broadcastRobotConfiguration();
}

void setCtrlType(Commander commander) {
    controllerData.commander = commander;
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
