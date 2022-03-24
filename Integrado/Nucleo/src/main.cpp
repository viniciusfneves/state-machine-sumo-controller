#define MACHINE_STACK_SIZE 1024 * 2

#include <Arduino.h>

#include <communications/PS4_controller/ps4_controller.hpp>
#include <communications/WiFi/WiFi.hpp>
#include <communications/WiFi/websockets_server/websockets_handlers.hpp>
#include <event_handler/event_handler.hpp>
#include <motors/drive_motors.hpp>
#include <sensors/sensors.hpp>
#include <sml.hpp>
#include <utilities/prototypes.hpp>

void setup() {
    // ?:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::?
    // *---- AVISO PARA USO DO CONTROLE DE PS4 ----* //
    // Para utilizar o controle de PS4 é necessário ou desativar os serviços Wi-Fi ou se conectar à um roteador.
    // Não é possível utilizar o ponto de acesso do ESP32 e o controle ao mesmo tempo
    // ?---------------------------------------------------------------------------------------------------------?
    // Comente "initController()" caso deseje desabilitar o BLE(Controle de PS4) para usar o AccessPoint do ESP
    // ?---------------------------------------------------------------------------------------------------------?
    // Comente "initAccessPoint()" e descomente "connectToWiFi("SSID", "PASSWORD")" para conectar o ESP à uma rede
    // existente no local. Descomente "initController()" para habilitar o controle de PS4 nesse caso
    // ?---------------------------------------------------------------------------------------------------------?
    // Caso queira desabilitar a funcionalidade de Wi-Fi comente: *É possível usar o controle de PS4 nessa opção*
    // * initAcessPoint()
    // * connectToWiFi()
    // * initWebSocketsServer()
    // ?:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::?

    // ! Configuração de Sensores e módulos do robô
    initStartModule();
    initMotors();
    initOpponentSensors();
    initEdgeSensors();

    // ! Processamento da Máquina de Estados
    xTaskCreate(execMachine, "ROBOTMACHINE", MACHINE_STACK_SIZE, NULL, 5, NULL);

    // ! Serviços de comunicação e controle
    // initController();
    initAccessPoint();
    // connectToWiFi("SSID", "PASSWORD");
    initWebSocketsServer();

    // Deleta as tasks do framework Arduino
    vTaskDelete(NULL);
}

void execMachine(void* _) {
    for (;;) {
        readSensors();
        processMachineEvents();
        vTaskDelay(4 / portTICK_PERIOD_MS);
    }
}