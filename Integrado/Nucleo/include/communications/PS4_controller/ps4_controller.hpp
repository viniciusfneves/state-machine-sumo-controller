#pragma once

#define CONTROLLER_MAC_ADDRESS "00:1a:7d:da:71:03"
#define CTRL_UPDATE_INTERVAL 32000  // us

#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#include <communications/PS4_controller/config_handler.hpp>
#include <configuration/set_configurations.hpp>
#include <dynamic_data/controller_data.hpp>
#include <event_handler/circular_buffer.hpp>
#include <utilities/calculus/calculus.hpp>

// Lê os comandos do controle e atua na máquina(robô) conforme necessário
void readControllerInputs() {
    if (PS4.PSButton()) {
        if (robotData.robotState == RobotState::stopped)
            addEventToQueue(Event::Arm);
    }
    if (PS4.Options()) {
        if (robotData.robotState != RobotState::stopped)
            addEventToQueue(Event::Disengage);
    }
    if (PS4.Right() && PS4.Triangle()) {
        if (robotConfiguration.mode == Mode::Auto) {
            setMode(Mode::RC);
        }
    }
    if (PS4.Left() && PS4.Triangle()) {
        if (robotConfiguration.mode == Mode::RC) {
            setMode(Mode::Auto);
        }
    }
    if (PS4.Up() && PS4.Triangle()) {
        if (robotData.robotState == RobotState::ready)
            addEventToQueue(Event::Start);
    }

    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);
    controllerData.isCharging = PS4.Charging();
    controllerData.battery    = PS4.Battery();
    xSemaphoreGive(xCtrlDataSemaphore);

    // Lê os comandos responsáveis pela movimentação do robô
    // Aqui também deverá ser feita a mixagem dos inputs antes de serem transformados em linear e angular
    if (controllerData.commander != Commander::bt_ps4)
        return;

    int    _trigger, _stick, _pedal, _wheel;
    double _linear, _angular;
    switch (controllerData.mapSettings) {
        case CommandMap::game_standard:
            _trigger = PS4.R2Value() - PS4.L2Value();
            _stick   = PS4.LStickX();
            _linear  = map_double(_trigger, -255, 255, -1, 1);
            _angular = map_double(_stick, -128, 127, -1, 1);

            if (abs(_angular) < 0.07)
                _angular = 0;
            break;

        case CommandMap::rc_standard:
            _pedal   = PS4.LStickY();
            _wheel   = PS4.RStickX();
            _linear  = map_double(_pedal, -128, 127, -1, 1);
            _angular = map_double(_wheel, -128, 127, -1, 1);

            if (abs(_angular) < 0.07)
                _angular = 0;
            if (abs(_linear) < 0.07)
                _linear = 0;
            break;

        case CommandMap::rc_inverted:
            _pedal   = PS4.RStickY();
            _wheel   = PS4.LStickX();
            _linear  = map_double(_pedal, -128, 127, -1, 1);
            _angular = map_double(_wheel, -128, 127, -1, 1);

            if (abs(_angular) < 0.07)
                _angular = 0;
            if (abs(_linear) < 0.07)
                _linear = 0;
            break;

        default:
            _angular = 0;
            _linear  = 0;
    }

    xSemaphoreTake(xCtrlDataSemaphore, portMAX_DELAY);

    switch (controllerData.filterSettings) {
        case CommandFilter::linear:
            controllerData.controllerInputs[Input::linearSpeed]  = _linear;
            controllerData.controllerInputs[Input::angularSpeed] = _angular;
            break;

        case CommandFilter::quadratic:
            if (_linear < 0)
                controllerData.controllerInputs[Input::linearSpeed] = -pow(_linear, 2);
            else
                controllerData.controllerInputs[Input::linearSpeed] = pow(_linear, 2);
            if (_angular < 0)
                controllerData.controllerInputs[Input::angularSpeed] = -pow(_angular, 2);
            else
                controllerData.controllerInputs[Input::angularSpeed] = pow(_angular, 2);
            break;

        case CommandFilter::cubic:
            controllerData.controllerInputs[Input::linearSpeed]  = pow(_linear, 3);
            controllerData.controllerInputs[Input::angularSpeed] = pow(_angular, 3);
            break;

        default:
            controllerData.controllerInputs[Input::linearSpeed]  = _linear;
            controllerData.controllerInputs[Input::angularSpeed] = _angular;
            break;
    }
    xSemaphoreGive(xCtrlDataSemaphore);
    if (robotConfiguration.mode == Mode::RC) {
        addEventToQueue(Event::Controller);
    }
}

void processControllerEvents(void* _) {
    for (;;) {  // Verifica se o controle está conectado antes de prosseguir com a função
        if (controllerData.isControllerConnected()) {
            readControllerInputs();

            //-- Configura as luzes do controle conforme a situação do robô - State Machine --//
            updateLights();
        }
        vTaskDelay(25 / portTICK_PERIOD_MS);
    }
}

void initController() {
    PS4.begin(CONTROLLER_MAC_ADDRESS);
    PS4.attachOnConnect([] {
        controllerData.controllerStatus = ControllerStatus::connected;
    });
    PS4.attachOnDisconnect([] {
        controllerData.controllerStatus = ControllerStatus::disconnected;
    });

    // ! Processamento da Thread do controle de PS4
    xTaskCreate(processControllerEvents, "PS4CTRL", 1024 * 3, NULL, 1, NULL);
}