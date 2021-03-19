#ifndef WEBSOCKETS_SERVER_HPP
#define WEBSOCKETS_SERVER_HPP

#include <WebSocketsServer.h>
#include <event_handler/circular_buffer.hpp>
#include "../../dynamic_data/handle_incoming_data.hpp"

WebSocketsServer webSocket(81); // Configura o serviço do WebSockets para a porta 81

void processWebSocketEvents()
{
    webSocket.loop();
}

// Lida com os dados recebidos do browser pelo WebSocket
void handleWSIncomingData(uint8_t client_id, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_ERROR:
        Serial.printf("Client id (%u) -> ERROR\n", client_id);
        break;
    case WStype_DISCONNECTED:
        Serial.printf("Client id (%u) -> Disconnecting\n", client_id);
        break;
    case WStype_CONNECTED:
        Serial.printf("Client Connected! Assigned ID: %u\n", client_id);
        addEventToQueue(Event::SendRobotConfig);
        break;
    case WStype_TEXT:
        Serial.printf("JSON recieved from Id: %u\n", client_id);
        processMessages(String((char *)payload));
        break;
    default:
        Serial.println("Tipo de mensagem WebSocket não programada recebida. Lide com ela em \"communications/WiFi/websocket_server -> Função (handleWSIncomingData)\"");
        break;
    }
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