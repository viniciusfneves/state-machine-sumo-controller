// A biblioteca SML precisa ser a primeira incluída no programa
#include <sml.hpp>

#ifdef SUMO3KG
#include <SPIFFS.h>
#include <communications/WiFi/access_point/wireless_access_point.hpp>
#include <communications/WiFi/http_server/http_server.hpp>
#include <communications/WiFi/websockets_server/webSockets_server.hpp>
#endif

#include <Arduino.h>
#include <event_handler/event_handler.hpp>
#include <motors/drive_motors.hpp>
#include <sensors/sensors.hpp>

void setup()
{
// Configurações específicas para o ESP32
#ifdef SUMO3KG
    Serial.begin(115200); // Porta Serial

    SPIFFS.begin(); // Inicia o File System do ESP32

    initAccessPointRouter();
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
#ifdef SUMO3KG
    processWebSocketEvents();
#endif
    processMachineEvents();
}