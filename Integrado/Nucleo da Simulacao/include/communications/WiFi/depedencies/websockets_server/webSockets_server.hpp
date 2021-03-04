#ifndef WEBSOCKETS_SERVER_HPP
#define WEBSOCKETS_SERVER_HPP

#include <WebSocketsServer.h>
#include "../../../JSON/json_handler.hpp"

WebSocketsServer webSocket(81); // Configura o serviço do WebSockets para a porta 81

void handleWSData()
{
    webSocket.loop();
}

void initWebSocketsServer()
{
    // Inicia o serviço de WebSockets
    webSocket.begin();
    Serial.println("WebSockets Server Started");

    // Configura qual função é executada a cada evento recebido pelo WebSocket
    webSocket.onEvent(handleWSIncomingData);
}

#endif