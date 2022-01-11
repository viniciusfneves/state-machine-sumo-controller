#if !defined(SEND_DATA_HPP)
#define SEND_DATA_HPP

#include <ArduinoJson.h>

#include <communications/WiFi/websockets_server/webSockets_server.hpp>
#include <configuration/configurations.hpp>
#include <configuration/specifications.hpp>
#include <dynamic_data/controller_data.hpp>
#include <dynamic_data/robot_data.hpp>

// Serializa objetos JSON e os envia para todos os clientes conectados no WebSocket
void serializeAndBroadcast(DynamicJsonDocument readings) {
    String JSONBuffer;

    serializeJson(readings, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
}

// Envia as informações estáticas do robô
// Essas informações são em sua maioria usadas para construir a interface do usuário e possibilitar uma interface de comunicação com o usuário
DynamicJsonDocument encodeRobotInfos() {
    StaticJsonDocument<512> infos;

    // Nome do robô
    infos["info"]["robot_name"] = robotSpecifications.robotName;

    // Quantidade de sensores
    infos["info"]["available_opponent_sensors"] = NUMBER_OF_OPPONENT_SENSORS;
    infos["info"]["available_edge_sensors"] = NUMBER_OF_EDGE_SENSORS;

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

    return infos;
}

// Envia as configurações atuais do robô
DynamicJsonDocument EncodeRobotConfiguration() {
    StaticJsonDocument<512> configs;

    // Parâmetros configuráveis para o modo Auto
    configs["configurations"]["start_time"] = robotConfiguration.startTime;
    configs["configurations"]["max_speed"] = robotConfiguration.maxSpeed;
    configs["configurations"]["pid"]["kp"] = robotConfiguration.Kp;
    configs["configurations"]["pid"]["ki"] = robotConfiguration.Ki;
    configs["configurations"]["pid"]["kd"] = robotConfiguration.Kd;

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
    }

    // Estratégia de busca
    switch (robotConfiguration.search) {
        case Search::none:
            configs["configurations"]["search"] = "none";
            break;
        case Search::radar:
            configs["configurations"]["search"] = "radar";
            break;
    }

    // Estratégia de perseguição
    switch (robotConfiguration.chase) {
        case Chase::standard:
            configs["configurations"]["chase"] = "standard";
            break;
    }

    return configs;
}

// Envia as leituras dos sensores de borda, dos sensores de oponente e da potência dos motores -> TELEMETRIA
DynamicJsonDocument encodeTelemetryData() {
    StaticJsonDocument<512> readings;

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
    for (int i = 0; i < NUMBER_OF_OPPONENT_SENSORS; i++) {
        readings["readings"]["opponent"][i] = robotData.opponentSensorsDetectionArray[i];
    }

    //Sensores de borda
    for (int i = 0; i < NUMBER_OF_EDGE_SENSORS; i++) {
        readings["readings"]["edge"][i] = robotData.edgeSensorsDetectionArray[i];
    }

    readings["readings"]["motor"][0] = robotData.motorsPower[0];
    readings["readings"]["motor"][1] = robotData.motorsPower[1];

    readings["controller"]["connection_status"] = controllerData.isControllerConnected() ? "connected" : "disconnected";
    readings["controller"]["battery"] = controllerData.battery;
    readings["controller"]["charging_status"] = controllerData.isCharging ? "true" : "false";

    return readings;
}

void broadcastRobotInfos() {
    DynamicJsonDocument infos = encodeRobotInfos();
    serializeAndBroadcast(infos);
};

void broadcastRobotConfiguration() {
    DynamicJsonDocument configs = EncodeRobotConfiguration();
    serializeAndBroadcast(configs);
};

void broadcastTelemetryData() {
    DynamicJsonDocument readings = encodeTelemetryData();
    serializeAndBroadcast(readings);
};
#endif  // SEND_DATA_HPP
