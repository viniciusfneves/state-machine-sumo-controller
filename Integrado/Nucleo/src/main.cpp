// A biblioteca SML precisa ser a primeira incluída no programa
#include <sml.hpp>
#include <Arduino.h>

#include <communications/PS4_controller/ps4_controller.hpp>
#include <communications/WiFi/WiFi.hpp>
#include <communications/WiFi/websockets_server/websockets_handlers.hpp>
#include <event_handler/event_handler.hpp>
#include <motors/drive_motors.hpp>
#include <performance/performance.hpp>
#include <sensors/sensors.hpp>

void setup() {
    // ---- AVISO PARA USO DO CONTROLE DE PS4 ---- //
    // Ao tentar utilizar o ESP32 como AcessPoint Wi-Fi e BLE para se comunicar com o controle,
    // o AcessPoint é terminado e o robô para de responder
    // ------------------------------------------ // ------------------------------------------ //
    // Para usar todas as features do Mesin Negara, comente "initAcessPoint()" e utilize "initController()"
    // junto com "connectToWiFi()"fornecendo à função o SSID e a senha da rede que deseja se conectar
    // ------------------------------------------ // ------------------------------------------ //
    // Se quiser utilizar o ESP como AcessPoint, comente "initController()" e tudo funcionará, exceto o controle de PS4

    initAccessPoint();
    // connectToWiFi("SSID", "PASSWORD");

    initWebSocketsServer();
    performance.setStackSize(CONFIG_ARDUINO_LOOP_STACK_SIZE);

    // Configuração de Sensores e módulos do robô
    initStartModule();
    initMotors();
    initOpponentSensors();
    initEdgeSensors();

    // initController();
}

void loop() {
    performance.startTimestamp = micros();

    processWebSocketEvents();
    pushTelemetry(micros());

    readSensors();
    processMachineEvents();

    performance.measure(micros(), uxTaskGetNumberOfTasks(), ESP.getFreeHeap(), uxTaskGetStackHighWaterMark(NULL));
}