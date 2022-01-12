#pragma once

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

    // Request da página de telemetria
    server.on("/telemetry", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/telemetry/telemetry.html"); });
    server.on("/telemetry.css", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/pages/telemetry/telemetry.css"); });

    // Request das depenências javascript
    server.on("/scripts/config.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/config.js"); });
    server.on("/scripts/telemetry.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/telemetry.js"); });
    server.on("/scripts/colors.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/colors.js"); });
    server.on("/scripts/websocket_handler.js", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/scripts/websocket_handler.js"); });

    // Request de arquivos de imagem
    server.on("/assets/debug_icon_bw.png", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/assets/debug_icon_bw.png"); });
    server.on("/assets/debug_icon_color.png", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/assets/debug_icon_color.png"); });
    server.on("/assets/ps4_all_bk.png", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/assets/ps4_all_bk.png"); });
    server.on("/assets/ps4_full.png", [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/assets/ps4_full.png"); });

    // Caso o usuário procure um endereço que não exista
    server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not found"); });
}

// Inicia o serviço HTTP
void initHTTPServer() {
    setRequestsResponse();
    server.begin();
}
