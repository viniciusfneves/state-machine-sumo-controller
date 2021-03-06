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

#endif // SEND_DATA_HPP
