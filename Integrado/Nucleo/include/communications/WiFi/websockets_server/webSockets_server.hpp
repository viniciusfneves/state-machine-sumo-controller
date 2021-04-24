#ifndef WEBSOCKETS_SERVER_HPP
#define WEBSOCKETS_SERVER_HPP

#include <WebSocketsServer.h>
#include <event_handler/circular_buffer.hpp>
#include <communications/data/data_handler.hpp>

WebSocketsServer webSocket(81); // Configura o serviço do WebSockets para a porta 81

// Lida com as requisições feitas ao server websocket
// Colocar no loop
void processWebSocketEvents()
{
    webSocket.loop();
}

// Lida com os dados recebidos pelo protocolo WebSocket
// -> Enviar somente JSON <-
void handleWSIncomingData(uint8_t client_id, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    // Caso haja um erro no recebimento de uma mensagem do cliente, expõe isso na Serial
    case WStype_ERROR:
        Serial.printf("ID do Cliente (%u) -> Erro na mensagem!\n", client_id);
        break;
    // Caso uma nova conexão seja aceita, envia automaticamente as configurações atuais do robô para o novo client
    case WStype_CONNECTED:
        addEventToQueue(Event::SendRobotConfig);
        break;
    // Caso a mensagem seja do tipo text (JSON), passa ela para ser decodificada pelo código
    case WStype_TEXT:
        processJsonMessage(String((char *)payload));
        break;
    default:
        break;
    }
}

// Inicia o servidor websocket
void initWebSocketsServer()
{
    // Inicia o serviço de WebSockets
    webSocket.begin();
    Serial.println("WebSockets Server Started");

    // Configura qual função é executada a cada evento recebido pelo WebSocket
    webSocket.onEvent(handleWSIncomingData);
}

#endif