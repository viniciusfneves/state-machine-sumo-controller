#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

AsyncWebServer server(80); // Configura o servidor HTTP para a porta 80

//Configura as instruções para lidar com os requests HTML
void setRequestsResponse()
{
    // Request da Home pelo cliente. Retorna index.html
    server.on("/", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/index.html"); });
    server.on("/style.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/style.css"); });
    server.on("/scripts/script.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/script.js"); });

    // Caso o usuário procure um endereço que não exista
    server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not found"); });
}

void initHTTPServer()
{
    setRequestsResponse();

    // Inicia o servidor HTTP
    server.begin();
    Serial.println("HTTP Server Started");
}

#endif