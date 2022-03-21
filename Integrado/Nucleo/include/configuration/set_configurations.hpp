#pragma once

#include <communications/data/robot_data_json_encoder.hpp>
#include <configuration/configurations.hpp>
#include <dynamic_data/controller_data.hpp>

// mode -> (enum) Mode
// Muda a configuração de modo de operação
void setMode(Mode mode) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.mode = mode;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

// strategy -> (enum) InitialMove
// Muda a configuração de estratégia de movimento inicial
void setInitialStrategy(InitialMove strategy) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.initialMove = strategy;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

// strategy -> (enum) Search
// Muda a configuração de estratégia de busca
void setSearchStrategy(Search strategy) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.search = strategy;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

// strategy -> (enum) Chase
// Muda a configuração de estratégia de perseguição
void setChaseStrategy(Chase strategy) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.chase = strategy;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

// Muda o tempo de acionamento do robô para começar a luta
void setStartTime(int time) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.startTime = abs(time);
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

// Altera a velocidade linear máxima global permitida para o robô
void setMaxSpeed(int newSpeed) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.maxSpeed = abs(newSpeed);
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}
// Altera a velocidade linear máxima global permitida para o robô
void setRadarSpeed(double newSpeed) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.radarSpeed = abs(newSpeed);
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setMaxAngularSpeedInChase(double newSpeed) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.maxAngularSpeedInChase = newSpeed;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setArcAngularSpeed(double newSpeed) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.arcAgularSpeed = newSpeed;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setArcTimeout(int time) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.arcTimeout = time;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setAngle(int newAngle) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.angle = newAngle;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setRotateRobotAngleBias(double bias) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.angleBias = bias;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setRotateRobotSpeedBias(double bias) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.speedBias = abs(bias);
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setInvertOpSensorReading(bool value) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.invertOpReading = value;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

// Altera os parâmetros para cálculo do controle PID
void changePIDSettings(double set_kp, double set_ki, double set_kd) {
    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);
    robotConfiguration.Kp = set_kp;
    robotConfiguration.Ki = set_ki;
    robotConfiguration.Kd = set_kd;
    xSemaphoreGive(xConfigSemaphore);
    broadcastRobotConfiguration();
}

void setCtrlType(Commander commander) {
    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);
    controllerData.commander = commander;
    xSemaphoreGive(xCtrlDataSemaphore);
    broadcastRobotConfiguration();
}

void setCtrlFilter(CommandFilter filter) {
    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);
    controllerData.filterSettings = filter;
    xSemaphoreGive(xCtrlDataSemaphore);
    broadcastRobotConfiguration();
}

void setCtrlMapping(CommandMap map) {
    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);
    controllerData.mapSettings = map;
    xSemaphoreGive(xCtrlDataSemaphore);
    broadcastRobotConfiguration();
}
