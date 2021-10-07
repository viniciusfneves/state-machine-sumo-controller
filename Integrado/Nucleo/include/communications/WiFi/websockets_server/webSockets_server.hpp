#ifndef WEBSOCKETS_SERVER_HPP
#define WEBSOCKETS_SERVER_HPP

#include <WebSocketsServer.h>
#include <event_handler/circular_buffer.hpp>
#include <communications/data/data_handler.hpp>

WebSocketsServer webSocket(81); // Configura o serviço do WebSockets para a porta 81

/* --> Colocar no loop <-- */
// Lida com as requisições feitas ao server websocket
void processWebSocketEvents()
{
    webSocket.loop();
}

/* --> Enviar somente JSON <-- */
// Lida com os dados recebidos pelo protocolo WebSocket
void handleWSIncomingData(uint8_t client_id, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    // Caso haja um erro no recebimento de uma mensagem do cliente
    case WStype_ERROR:
        break;
    // Caso uma nova conexão seja aceita
    case WStype_CONNECTED:
        addEventToQueue(Event::SetUpClient);
        break;
    // Caso a mensagem seja do tipo text
    case WStype_TEXT:
        processJsonMessage(String((char *)payload));
        break;
    default:
        break;
    }
}

// Inicia o serviço websocket
void initWebSocketsServer()
{
    webSocket.begin();

    // Configura qual função é executada a cada evento recebido pelo WebSocket
    webSocket.onEvent(handleWSIncomingData);
}

#endif