#if !defined(SEND_DATA_HPP)
#define SEND_DATA_HPP

#include <ArduinoJson.h>
#include <configuration/configurations.hpp>
#include "../WiFi/websockets_server/webSockets_server.hpp"

void broadcastConfigurations()
{
    StaticJsonDocument<128> configs;
    String JSONBuffer;

    configs["robot_name"] = robotConfiguration.robot_name;
    
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

void broadcastOPReadings(bool opSensorArray[]){
    StaticJsonDocument<128> readings;
    String JSONBuffer;

    readings["readings"]["opponent"][0] = opSensorArray[0];
    readings["readings"]["opponent"][1] = opSensorArray[1];
    readings["readings"]["opponent"][2] = opSensorArray[2];
    readings["readings"]["opponent"][3] = opSensorArray[3];
    readings["readings"]["opponent"][4] = opSensorArray[4];

    serializeJson(readings, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
};

void broadcastEdgeReadings(bool edgeSensorArray[]){
    StaticJsonDocument<128> readings;
    String JSONBuffer;

    readings["readings"]["edge"][0] = edgeSensorArray[0];
    readings["readings"]["edge"][1] = edgeSensorArray[1];

    serializeJson(readings, JSONBuffer);
    webSocket.broadcastTXT(JSONBuffer);
};

#endif // SEND_DATA_HPP
