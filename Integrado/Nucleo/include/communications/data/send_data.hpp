#if !defined(SEND_DATA_HPP)
#define SEND_DATA_HPP

#include <ArduinoJson.h>

#include <configuration/configurations.hpp>
#include <configuration/specifications.hpp>

#include "../WiFi/websockets_server/webSockets_server.hpp"

// Serializa objetos JSON e os envia para todos os clientes conectados no WebSocket
void serializeAndBroadcast(DynamicJsonDocument readings) {
    String JSONBuffer;

    serializeJson(readings, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
}

// Envia as informações estáticas do robô
// Essas informações são em sua maioria usadas para construir a interface do usuário e possibilitar uma interface de comunicação com o usuário
void broadcastRobotInfos() {
    StaticJsonDocument<512> configs;

    // Nome do robô
    configs["info"]["robot_name"] = robotSpecifications.robotName;

    // Quantidade de sensores
    configs["info"]["available_opponent_sensors"] = NUMBER_OF_OPPONENT_SENSORS;
    configs["info"]["available_edge_sensors"] = NUMBER_OF_EDGE_SENSORS;

    // Estratégias disponíveis em cada um dos movimentos possíveis
    for (int index = 0; index < initialStrategies.size(); index++) {
        configs["info"]["available_initial_strategies"][index] = initialStrategies[index];
    }
    for (int index = 0; index < searchStrategies.size(); index++) {
        configs["info"]["available_search_strategies"][index] = searchStrategies[index];
    }
    for (int index = 0; index < chaseStrategies.size(); index++) {
        configs["info"]["available_chase_strategies"][index] = chaseStrategies[index];
    }

    serializeAndBroadcast(configs);
}

// Envia as configurações atuais do robô
void broadcastRobotConfiguration() {
    StaticJsonDocument<512> configs;

    // Parâmetros configuráveis
    configs["configurations"]["start_time"] = robotConfiguration.startTime;
    configs["configurations"]["max_speed"] = robotConfiguration.maxSpeed;
    configs["configurations"]["pid"]["kp"] = robotConfiguration.Kp;
    configs["configurations"]["pid"]["ki"] = robotConfiguration.Ki;
    configs["configurations"]["pid"]["kd"] = robotConfiguration.Kd;

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

    serializeAndBroadcast(configs);
}

// Envia as leituras dos sensores de borda, dos sensores de oponente e da potência dos motores -> TELEMETRIA
void broadcastTelemetryData() {
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

    readings["controller"]["status"] = robotData.controllerStatus == ControllerStatus::connected ? "connected" : "disconnected";

    serializeAndBroadcast(readings);
}
#endif  // SEND_DATA_HPP
