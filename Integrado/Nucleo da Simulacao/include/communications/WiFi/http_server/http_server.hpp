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

    // Request da página de configurações do robô
    server.on("/config", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/config/config.html"); });
    server.on("/config.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/config/config.css"); });
    server.on("/scripts/config.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/config.js"); });

    // Request da página de telemetria do robô
    server.on("/telemetry", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/telemetry/telemetry.html"); });
    server.on("/telemetry.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/telemetry/telemetry.css"); });
    server.on("/scripts/telemetry.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/telemetry.js"); });

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