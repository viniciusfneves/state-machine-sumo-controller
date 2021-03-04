#include <Arduino.h>
#include <SPIFFS.h>
#include <event_handler/event_handler.hpp>
#include <communications/WiFi/depedencies/acess_point/wireless_acess_point.hpp>
#include <communications/WiFi/depedencies/http_server/http_server.hpp>
#include <communications/WiFi/depedencies/websockets_server/webSockets_server.hpp>

void setup()
{
// Configurações específicas para o ESP32
#ifdef SUMO3KG
    Serial.begin(115200); // Porta Serial

    SPIFFS.begin(); // Inicia o File System do ESP32

    initAcessPointRouter();
    initHTTPServer();
    initWebSocketsServer();
#endif

#ifdef SUMOMINI
    Serial.begin(9600);
#endif

    initMotors();
    initOpponentSensors();
    initEdgeSensors();
}

void loop()
{
    handleWSData();
    processEvents();
}