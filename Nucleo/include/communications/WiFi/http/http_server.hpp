#pragma once

#include <ESPAsyncWebServer.h>
#include <WiFi.h>

AsyncWebServer server(80);

void initHTTPServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", WiFi.localIP().toString());
    });

    server.begin();
}
