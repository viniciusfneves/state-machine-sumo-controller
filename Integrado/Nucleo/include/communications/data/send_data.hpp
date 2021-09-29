#if !defined(SEND_DATA_HPP)
#define SEND_DATA_HPP

#include <ArduinoJson.h>
#include <configuration/configurations.hpp>
#include <configuration/specifications.hpp>
#include "../WiFi/websockets_server/webSockets_server.hpp"

// Serializa objetos JSON e os envia para todos os clientes conectados no WebSocket
void serializeAndBroadcast(DynamicJsonDocument readings)
{
    String JSONBuffer;

    serializeJson(readings, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
}

// Envia as configurações atuais do robô
void broadcastRobotConfiguration()
{
    StaticJsonDocument<320> configs;

    // Nome do robô
    configs["robot_name"] = robotSpecifications.robotName;

    // Quantidade de sensores
    configs["available_opponent_sensors"] = NUMBER_OF_OPPONENT_SENSORS;
    configs["available_edge_sensors"] = NUMBER_OF_EDGE_SENSORS;

    // Parâmetros configuráveis
    configs["configurations"]["settings"]["start_time"] = robotConfiguration.startTime;
    configs["configurations"]["settings"]["max_speed"] = robotConfiguration.maxSpeed;
    configs["configurations"]["settings"]["pid"]["kp"] = robotConfiguration.Kp;
    configs["configurations"]["settings"]["pid"]["ki"] = robotConfiguration.Ki;
    configs["configurations"]["settings"]["pid"]["kd"] = robotConfiguration.Kd;

    // Estado de execução
    switch (robotConfiguration.robotState)
    {
    case RobotState::ready:
        configs["robot_status"] = "ready";
        break;
    case RobotState::stopped:
        configs["robot_status"] = "stopped";
        break;
    case RobotState::starting:
        configs["robot_status"] = "starting";
        break;
    case RobotState::exec_initial:
        configs["robot_status"] = "exec_initial";
        break;
    case RobotState::exec_search:
        configs["robot_status"] = "exec_search";
        break;
    case RobotState::exec_chase:
        configs["robot_status"] = "exec_chase";
        break;
    }

    // Modo de operação
    switch (robotConfiguration.mode)
    {
    case Mode::Auto:
        configs["configurations"]["mode"] = "auto";
        break;
    case Mode::RC:
        configs["configurations"]["mode"] = "rc";
        break;
    }

    // Estratégia inicial
    switch (robotConfiguration.initialMove)
    {
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
    switch (robotConfiguration.search)
    {
    case Search::none:
        configs["configurations"]["search"] = "none";
        break;
    case Search::radar:
        configs["configurations"]["search"] = "radar";
        break;
    }

    // Estratégia de perseguição
    switch (robotConfiguration.chase)
    {
    case Chase::standard:
        configs["configurations"]["chase"] = "standard";
        break;
    }

    serializeAndBroadcast(configs);
}

// Envia as leituras dos sensores de borda, dos sensores de oponente e da potência dos motores -> TELEMETRIA
void broadcastTelemetryData(bool opSensorArray[], bool edgeSensorArray[], int powerOnWheels[])
{
    StaticJsonDocument<320> readings;

    // Sensores de oponente
    for (int i = 0; i < NUMBER_OF_OPPONENT_SENSORS; i++)
    {
        readings["readings"]["opponent"][i] = opSensorArray[i];
    }

    //Sensores de borda
    for (int i = 0; i < NUMBER_OF_EDGE_SENSORS; i++)
    {
        readings["readings"]["edge"][i] = edgeSensorArray[i];
    }

    readings["readings"]["motor"][0] = powerOnWheels[0];
    readings["readings"]["motor"][1] = powerOnWheels[1];

    serializeAndBroadcast(readings);
}
#endif // SEND_DATA_HPP
