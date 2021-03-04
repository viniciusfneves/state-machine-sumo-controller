#ifndef WIRELESS_COM_HANDLER_HPP
#define WIRELESS_COM_HANDLER_HPP

#include "depedencies/acess_point/wireless_acess_point.hpp"
#include "depedencies/http_server/http_server.hpp"
#include "depedencies/websockets_server/webSockets_server.hpp"

// Gerencia a inicialização da comunicação Wi-Fi
// Abre um Acess Point & Inicia o servidor HTTP & Inicia o servidor WebSocket
void initCommunications()
{
    initAcessPointRouter();
    initHTTPServer();
    initWebSocketsServer();
}

#endif