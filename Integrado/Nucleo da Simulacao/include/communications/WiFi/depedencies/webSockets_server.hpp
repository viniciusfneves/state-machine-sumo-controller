#ifndef WEBSOCKETS_SERVER_HPP
#define WEBSOCKETS_SERVER_HPP

#include <WebSocketsServer.h>

WebSocketsServer webSocket(81); // Configura o serviço do WebSockets para a porta 81

// Lida com a troca de dados entre server e clients pelo protocolo WebSockets
void handleWSData()
{
    webSocket.loop();
}

// Lida com os dados recebidos do browser pelo WebSocket
void handleWSIncomingData(uint8_t client_id, WStype_t type, uint8_t *data, size_t length)
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
        break;
    case WStype_TEXT:
        Serial.printf("Message recieved from id (%u) -> %s\n", client_id, data);
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