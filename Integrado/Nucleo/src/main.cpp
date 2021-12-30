// A biblioteca SML precisa ser a primeira incluída no programa
#include <Arduino.h>

#include <event_handler/event_handler.hpp>
#include <motors/drive_motors.hpp>
#include <sensors/sensors.hpp>
#include <sml.hpp>

#ifdef ESP32_ENV
#include <SPIFFS.h>

#include <communications/PS4_controller/ps4_controller.hpp>
#include <communications/WiFi/access_point/wireless_access_point.hpp>
#include <communications/WiFi/http_server/http_server.hpp>
#include <communications/WiFi/websockets_server/webSockets_server.hpp>
#endif

void setup() {
// Configurações do ambiente para Arduino
#ifdef ARDUINO_ENV
    Serial.begin(9600);
#endif

// Configurações do ambiente para ESP32
#ifdef ESP32_ENV
    SPIFFS.begin();  // Inicia o File System do ESP32

    // ---- AVISO PARA USO DO CONTROLE DE PS4 ---- //
    // O uso do controle juntamente com os WebServers só pode ser feito utilizando uma rede WiFi externa
    // Ao tentar utilizar o ESP32 como AcessPoint e conectar e ler o controle, o AcessPoint é terminado e portanto não será
    // mais possível se conectar aos servers remotamente
    // ------------------------------------------ // ------------------------------------------ //
    // Para usar todas as features do Mesin Negara, comente "initAcessPoint()" e utilize "initController()"
    // junto com "connectToWiFi()"fornecendo à função o SSID e a senha da rede que deseja se conectar
    // Futuramente: Será implementado um serviço mDNS para facilitar a conexão via redes externas onde o IP é dinâmico
    // ------------------------------------------ // ------------------------------------------ //
    //initController();
    //connectToWiFi("SSID", "PASSWORD");

    initAccessPoint();
    initHTTPServer();
    initWebSocketsServer();
#endif

    // Configuração de Sensores e módulos do robô
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