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
    server.on("/config/config.html", [](AsyncWebServerRequest *request) { request->redirect("/config"); });
    server.on("/telemetry/telemetry.html", [](AsyncWebServerRequest *request) { request->redirect("/telemetry"); });

    // Request da página de configurações
    server.serveStatic("/config", SPIFFS, "/pages/config/config.html").setAuthentication("admin", "admin");
    server.serveStatic("/config.css", SPIFFS, "/pages/config/config.css");

    // Request da página de telemetria
    server.serveStatic("/telemetry", SPIFFS, "/pages/telemetry/telemetry.html");
    server.serveStatic("/telemetry.css", SPIFFS, "/pages/telemetry/telemetry.css");

    // Request das depenências javascript
    server.serveStatic("/scripts/config.js", SPIFFS, "/scripts/config.js");
    server.serveStatic("/scripts/telemetry.js", SPIFFS, "/scripts/telemetry.js");
    server.serveStatic("/scripts/colors.js", SPIFFS, "/scripts/colors.js");
    server.serveStatic("/scripts/websocket_handler.js", SPIFFS, "/scripts/websocket_handler.js");

    // Request de arquivos de imagem
    server.serveStatic("/assets/debug_icon_bw.png", SPIFFS, "/assets/debug_icon_bw.png");
    server.serveStatic("/assets/debug_icon_color.png", SPIFFS, "/assets/debug_icon_color.png");
    server.serveStatic("/assets/ps4_all_bk.png", SPIFFS, "/assets/ps4_all_bk.png");
    server.serveStatic("/assets/ps4_full.png", SPIFFS, "/assets/ps4_full.png");

    // Caso o usuário procure um endereço que não exista
    server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not found"); });
}

// Inicia o serviço HTTP
void initHTTPServer() {
    SPIFFS.begin();  // Inicia o File System do ESP32

    setRequestsResponse();
    server.begin();
}
