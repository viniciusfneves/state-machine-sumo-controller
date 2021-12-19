// A biblioteca SML precisa ser a primeira incluída no programa
#include <Arduino.h>

#include <event_handler/event_handler.hpp>
#include <motors/drive_motors.hpp>
#include <sensors/sensors.hpp>
#include <sml.hpp>

#ifdef ESP32_ENV
#include <SPIFFS.h>

#include <communications/WiFi/access_point/wireless_access_point.hpp>
#include <communications/WiFi/http_server/http_server.hpp>
#include <communications/WiFi/websockets_server/webSockets_server.hpp>
#endif

void setup() {
// Configurações específicas para o ESP32
#ifdef ESP32_ENV
    SPIFFS.begin();  // Inicia o File System do ESP32

    initAccessPoint();
    initHTTPServer();
    initWebSocketsServer();
#endif

#ifdef ARDUINO_ENV
    Serial.begin(9600);
#endif

    initStartModule();
    initMotors();
    initOpponentSensors();
    initEdgeSensors();
}

void loop() {
#ifdef ESP32_ENV
    processWebSocketEvents();
#endif
    readSensors();
    processMachineEvents();
}