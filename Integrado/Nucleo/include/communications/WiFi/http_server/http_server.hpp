#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Configura o servidor HTTP para a porta 80
AsyncWebServer server(80);

//Configura as respostas para os requests HTML
void setRequestsResponse() {
    // Request da Home -> Redireciona para a página de configurações
    server.on("/", [](AsyncWebServerRequest *request) { request->redirect("/config"); });

    // Request da página de configurações
    server.on("/config", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/config/config.html"); });
    server.on("/config.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/config/config.css"); });
    server.on("/scripts/config.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/config.js"); });

    // Request da página de telemetria
    server.on("/telemetry", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/telemetry/telemetry.html"); });
    server.on("/telemetry.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/telemetry/telemetry.css"); });
    server.on("/scripts/telemetry.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/telemetry.js"); });

    // Caso o usuário procure um endereço que não exista
    server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not found"); });
}

// Inicia o serviço HTTP
void initHTTPServer() {
    setRequestsResponse();
    server.begin();
}

#endif