#if !defined(SEND_DATA_HPP)
#define SEND_DATA_HPP

#include <ArduinoJson.h>
#include <configuration/configurations.hpp>
#include <configuration/specifications.hpp>
#include "../WiFi/websockets_server/webSockets_server.hpp"

void broadcastConfigurations()
{
    StaticJsonDocument<128> configs;
    String JSONBuffer;

    configs["robot_name"] = robotSpecifications.robotName;

    switch (robotConfiguration.mode)
    {
    case Mode::Auto:
        configs["configurations"]["mode"] = "auto";
        break;
    case Mode::RC:
        configs["configurations"]["mode"] = "rc";
        break;
    }
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
    switch (robotConfiguration.search)
    {
    case Search::none:
        configs["configurations"]["search"] = "none";
        break;
    case Search::radar:
        configs["configurations"]["search"] = "radar";
        break;
    }
    switch (robotConfiguration.chase)
    {
    case Chase::standard:
        configs["configurations"]["chase"] = "standard";
        break;
    }

    // Serializa o JSON em um buffer e depois o envia para os clientes do WebSocket
    serializeJson(configs, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
}

// Serializa qualquer objeto JSON e envia para todos os clientes conectados no WebSocket
void serializeAndBroadcast(DynamicJsonDocument readings)
{
    String JSONBuffer;

    serializeJson(readings, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
}

// Envia as leituras dos sensores de oponentes para todos os clientes do WebSockets -> TELEMETRIA
void broadcastSensorsReadings(bool opSensorArray[], bool edgeSensorArray[])
{
    StaticJsonDocument<256> readings;

    readings["readings"]["opponent"][0] = opSensorArray[0];
    readings["readings"]["opponent"][1] = opSensorArray[1];
    readings["readings"]["opponent"][2] = opSensorArray[2];
    readings["readings"]["opponent"][3] = opSensorArray[3];
    readings["readings"]["opponent"][4] = opSensorArray[4];

    readings["readings"]["edge"][0] = edgeSensorArray[0];
    readings["readings"]["edge"][1] = edgeSensorArray[1];

    serializeAndBroadcast(readings);
}


// Envia as leituras das potências dos motores para todos os clientes do WebSockets -> TELEMETRIA
void broadcastMotorsPower(int left_motor_PWM, int right_motor_PWM)
{
    StaticJsonDocument<64> readings;

    readings["readings"]["motor"][0] = left_motor_PWM;
    readings["readings"]["motor"][1] = right_motor_PWM;

    serializeAndBroadcast(readings);
}

#endif // SEND_DATA_HPP
