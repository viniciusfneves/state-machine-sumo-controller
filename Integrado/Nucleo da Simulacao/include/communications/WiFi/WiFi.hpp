#ifndef WIFI_HPP
#define WIFI_HPP

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>

const char *ssid = "ESP32";        // Nome da rede - SSID
const char *password = "12345678"; // Senha da rede

AsyncWebServer server(80);      // Configura o servidor HTTP para a porta 80
WebSocketsServer webSocket(81); // Configura o serviço do WebSockets para a porta 81

//Configura as instruções para lidar com os requests HTML
void setRequestsResponse()
{
    // Request da Home pelo cliente. Retorna index.html
    server.on("/", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/index.html"); });
    server.on("/style.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/style.css"); });
    server.on("/js/script.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/js/script.js"); });

    // Caso o usuário procure um endereço que não exista
    server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not found"); });
}

// Lida com os dados recebidos do browser pelo WebSocket
void handleWSIncomingData(uint8_t client_id, WStype_t type, uint8_t *data, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("(%u) Disconnecting\n", client_id);
        break;
    case WStype_CONNECTED:
        Serial.printf("Client Connected! Assigned ID: %u\n", client_id);
        break;
    case WStype_TEXT:
        Serial.printf("(%u) Message recieved -> %s\n", client_id, data);
        break;
    case WStype_ERROR:
        break;
    }
}

// Lida com a troca de dados entre server e clients pelo protocolo WebSockets
void handleWSData()
{
    webSocket.loop();
}

// Realiza as configurações necessárias para a parte de comunicação
// do ESP32
void initCommunications()
{
    // Cria a rede Wi-Fi própria do ESP com os parametros de
    // nome da rede e senha
    WiFi.softAP(ssid, password);
    delay(100);
    // Printa o endereço IP do Server na Serial
    Serial.println(WiFi.softAPIP());

    // Inicia o servidor HHTP
    server.begin();
    Serial.println("HTTP Server Started");

    setRequestsResponse();

    // Inicia o serviço de WebSockets
    webSocket.begin();
    Serial.println("WebSockets Server Started");

    // Configura qual ação tomar a cada evento recebido pelo WebSocket
    webSocket.onEvent(handleWSIncomingData);
}

#endif