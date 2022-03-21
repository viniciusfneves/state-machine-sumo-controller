#pragma once

#include <ArduinoJson.h>

#include <communications/WiFi/websockets_server/webSockets_server.hpp>
#include <configuration/configurations.hpp>
#include <configuration/specifications.hpp>
#include <dynamic_data/controller_data.hpp>
#include <dynamic_data/robot_data.hpp>
#include <performance/performance.hpp>

// Serializa objetos JSON e os envia para todos os clientes conectados no WebSocket
void serializeAndBroadcast(DynamicJsonDocument readings) {
    String JSONBuffer;

    serializeJson(readings, JSONBuffer);
    wss.broadcastTXT(JSONBuffer);
}

// Envia as informações estáticas do robô
// Essas informações são em sua maioria usadas para construir a interface do usuário e possibilitar uma interface de comunicação com o usuário
DynamicJsonDocument encodeRobotInfos() {
    StaticJsonDocument<2048> infos;

    // Nome do robô
    infos["info"]["robot_name"] = robotSpecifications.robotName;

    // Estratégias disponíveis no robô
    for (int index = 0; index < modesAvailable.size(); index++) {
        infos["info"]["available_modes"][index] = modesAvailable[index];
    }
    for (int index = 0; index < initialStrategies.size(); index++) {
        infos["info"]["available_initial_strategies"][index] = initialStrategies[index];
    }
    for (int index = 0; index < searchStrategies.size(); index++) {
        infos["info"]["available_search_strategies"][index] = searchStrategies[index];
    }
    for (int index = 0; index < chaseStrategies.size(); index++) {
        infos["info"]["available_chase_strategies"][index] = chaseStrategies[index];
    }
    for (int index = 0; index < ctrl_types.size(); index++) {
        infos["info"]["available_ctrl_types"][index] = ctrl_types[index];
    }
    for (int index = 0; index < ctrl_maps.size(); index++) {
        infos["info"]["available_ctrl_maps"][index] = ctrl_maps[index];
    }
    for (int index = 0; index < ctrl_filters.size(); index++) {
        infos["info"]["available_ctrl_filters"][index] = ctrl_filters[index];
    }

    return infos;
}

// Envia as configurações atuais do robô
DynamicJsonDocument EncodeRobotConfiguration() {
    StaticJsonDocument<512> configs;

    xSemaphoreTake(xConfigSemaphore, portMAX_DELAY);

    // Parâmetros configuráveis para o modo Auto
    configs["configurations"]["start_time"]            = robotConfiguration.startTime;
    configs["configurations"]["max_speed"]             = robotConfiguration.maxSpeed;
    configs["configurations"]["rotate_angle_bias"]     = robotConfiguration.angleBias;
    configs["configurations"]["rotate_speed_bias"]     = robotConfiguration.speedBias;
    configs["configurations"]["max_speed_in_chase"]    = robotConfiguration.maxAngularSpeedInChase;
    configs["configurations"]["arc_angular_speed"]     = robotConfiguration.arcAgularSpeed;
    configs["configurations"]["arc_rot_initial_angle"] = robotConfiguration.angle;
    configs["configurations"]["arc_timeout"]           = robotConfiguration.arcTimeout;
    configs["configurations"]["radar_speed"]           = robotConfiguration.radarSpeed;
    configs["configurations"]["pid"]["kp"]             = robotConfiguration.Kp;
    configs["configurations"]["pid"]["ki"]             = robotConfiguration.Ki;
    configs["configurations"]["pid"]["kd"]             = robotConfiguration.Kd;

    // Modo de operação
    switch (robotConfiguration.mode) {
        case Mode::Auto:
            configs["configurations"]["mode"] = "auto";
            break;
        case Mode::RC:
            configs["configurations"]["mode"] = "rc";
            break;
    }

    // Estratégia inicial
    switch (robotConfiguration.initialMove) {
        case InitialMove::none:
            configs["configurations"]["initial_move"] = "none";
            break;
        case InitialMove::full_frente:
            configs["configurations"]["initial_move"] = "full_frente";
            break;
        case InitialMove::zig_zag:
            configs["configurations"]["initial_move"] = "zig_zag";
            break;
        case InitialMove::arco:
            configs["configurations"]["initial_move"] = "arco";
            break;
    }

    // Estratégia de busca
    switch (robotConfiguration.search) {
        case Search::none:
            configs["configurations"]["search"] = "none";
            break;
        case Search::radar:
            configs["configurations"]["search"] = "radar";
            break;
        case Search::teco:
            configs["configurations"]["search"] = "teco";
            break;
    }

    // Estratégia de perseguição
    switch (robotConfiguration.chase) {
        case Chase::standard:
            configs["configurations"]["chase"] = "standard";
            break;
    }

    xSemaphoreGive(xConfigSemaphore);
    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);

    // Parâmetros configuráveis para o modo RC
    configs["configurations"]["controller"]["commander"] = controllerData.commander == Commander::bt_ps4 ? "bt_ps4" : "radio";
    switch (controllerData.mapSettings) {
        case CommandMap::rc_standard:
            configs["configurations"]["controller"]["mapping"] = "rc_standard";
            break;

        case CommandMap::rc_inverted:
            configs["configurations"]["controller"]["mapping"] = "rc_inverted";
            break;

        case CommandMap::game_standard:
            configs["configurations"]["controller"]["mapping"] = "game_standard";
            break;
    }
    switch (controllerData.filterSettings) {
        case CommandFilter::linear:
            configs["configurations"]["controller"]["filter"] = "linear";
            break;

        case CommandFilter::quadratic:
            configs["configurations"]["controller"]["filter"] = "quadratic";
            break;

        case CommandFilter::cubic:
            configs["configurations"]["controller"]["filter"] = "cubic";
            break;
    }
    xSemaphoreGive(xCtrlDataSemaphore);

    return configs;
}

// Envia as leituras dos sensores de borda, dos sensores de oponente e da potência dos motores -> TELEMETRIA
DynamicJsonDocument encodeTelemetryData() {
    StaticJsonDocument<512> readings;

    xSemaphoreTake(xRobotDataSemaphore, portMAX_DELAY);

    // Estado de execução
    switch (robotData.robotState) {
        case RobotState::ready:
            readings["readings"]["robot_status"] = "ready";
            break;
        case RobotState::stopped:
            readings["readings"]["robot_status"] = "stopped";
            break;
        case RobotState::starting:
            readings["readings"]["robot_status"] = "starting";
            break;
        case RobotState::exec_initial:
            readings["readings"]["robot_status"] = "exec_initial";
            break;
        case RobotState::exec_search:
            readings["readings"]["robot_status"] = "exec_search";
            break;
        case RobotState::exec_chase:
            readings["readings"]["robot_status"] = "exec_chase";
            break;
        case RobotState::exec_controller:
            readings["readings"]["robot_status"] = "exec_controller";
            break;
    }

    // Sensores de oponente
    for (auto reading = robotData.opponentSensorsDetectionArray.begin(); reading != robotData.opponentSensorsDetectionArray.end(); reading++) {
        readings["readings"]["opponent"][reading->first] = reading->second;
    }

    // Sensores de borda
    for (auto reading = robotData.edgeSensorsDetectionArray.begin(); reading != robotData.edgeSensorsDetectionArray.end(); reading++) {
        readings["readings"]["edge"][reading->first] = reading->second;
    }

    readings["readings"]["motor"][0] = robotData.motorsPower[0];
    readings["readings"]["motor"][1] = robotData.motorsPower[1];

    xSemaphoreGive(xRobotDataSemaphore);
    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);

    if (controllerData.isControllerConnected()) {
        readings["controller"]["connection_status"] = "connected";
        readings["controller"]["charging_status"]   = controllerData.isCharging ? "true" : "false";
        readings["controller"]["battery"]           = controllerData.battery;
        readings["controller"]["raw_linear"]        = controllerData.controllerInputs[Input::linearSpeed];
        readings["controller"]["raw_angular"]       = controllerData.controllerInputs[Input::angularSpeed];
    } else
        readings["controller"]["connection_status"] = "disconnected";

    readings["performance"]["loop_task"]       = performance.timeToExecute;
    readings["performance"]["n_tasks"]         = performance.numberOfTaks;
    readings["performance"]["memory_usage"]    = performance.freeMemory;
    readings["performance"]["stack_max_usage"] = performance.BstackMaxUsage;

    xSemaphoreGive(xCtrlDataSemaphore);

    return readings;
}

void broadcastRobotInfos() {
    serializeAndBroadcast(encodeRobotInfos());
}

void broadcastRobotConfiguration() {
    serializeAndBroadcast(EncodeRobotConfiguration());
};

void broadcastTelemetryData() {
    serializeAndBroadcast(encodeTelemetryData());
};
