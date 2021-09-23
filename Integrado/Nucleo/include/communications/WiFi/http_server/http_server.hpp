#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <communications/data/data_handler.hpp>

// Configura o servidor HTTP para a porta 80
AsyncWebServer server(80);

//Configura as respostas para os requests HTML
void setRequestsResponse()
{
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

    // Requests na página de informações do controle
    
    // Caso o request seja do tipo GET -> Retorna um erro e uma mensagem
    server.on("/controller", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Exclusivo para POST requests"); });

    
    // Caso o request seja do tipo POST -> Espera receber os parametros linear e angular.
    // Esses parametros são repassados para o código como JSON para serem interpretados como comandos do controle para o modo RC
    /* --> ERROS COM O CONTROLE <-- */
    // Caso não haja os parâmetros esperados, apresenta erro no código!!! -> Implementar futuras verificações para inibir isso
    server.on("/controller", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
        String jsonpayload = "";
        for (size_t i = 0; i < len; i++) {
            jsonpayload += char(data[i]);
        }
        processJsonMessage(jsonpayload);
        request->send(200, "text/plain", "Ok");
    });

    // Caso o usuário procure um endereço que não exista
    server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not found"); });
}

// Inicia o serviço HTTP
void initHTTPServer()
{
    setRequestsResponse();
    server.begin();
}

#endif