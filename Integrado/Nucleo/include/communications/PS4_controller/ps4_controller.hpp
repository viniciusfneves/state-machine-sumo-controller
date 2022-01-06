#ifndef PS4_CONTROLLER_HPP
#define PS4_CONTROLLER_HPP

#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#include "dynamic_data/dynamic_data.hpp"

#define CONTROLLER_MAC_ADDRESS "00:1a:7d:da:71:03"

namespace ps4AmbientVariables {
unsigned long lastControllerUpdateTimestamp = 0UL;
unsigned long lastlightUpdateTimestamp = 0UL;
bool alternateController = true;
bool timeToChange = false;
}  // namespace ps4AmbientVariables

enum LightMode {
    l_static,
    flashing,
    fast_flashing,
    slow_flashing,
    flashing_dual_colors,
    slow_flashing_dual_colors
};

void initController() {
    PS4.begin(CONTROLLER_MAC_ADDRESS);
    PS4.attachOnConnect([] {
        robotData.controllerStatus = ControllerStatus::connected;
    });
    PS4.attachOnDisconnect([] {
        robotData.controllerStatus = ControllerStatus::disconnected;
    });
}

// Lê os comandos do controle e atua na máquina(robô) conforme necessário
void readControllerInputs() {
    if (PS4.Options()) {
        if (robotData.robotState == RobotState::stopped)
            addEventToQueue(Event::Arm);
    }
    if (PS4.PSButton()) {
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

    // Lê os comandos responsáveis pela movimentação do robô
    // Aqui também deverá ser feita a mixagem dos inputs antes de serem transformados em linear e angular
    int _trigger = PS4.R2Value() - PS4.L2Value();
    int _stick = PS4.LStickX();
    double _linear = map_double(_trigger, -255, 255, -1, 1);
    double _angular = map_double(_stick, -128, 127, -1, 1);
    if (abs(_angular) < 0.07)
        _angular = 0;
    robotData.controllerInputs[Input::linearSpeed] = pow(_linear, 3);
    robotData.controllerInputs[Input::angularSpeed] = pow(_angular, 3);

    if (robotConfiguration.mode == Mode::RC) {
        addEventToQueue(Event::Controller);
    }
}

void configController(unsigned short* lightParams, LightMode mode) {
    unsigned short f_r = lightParams[0];
    unsigned short f_g = lightParams[1];
    unsigned short f_b = lightParams[2];
    unsigned short s_r = lightParams[3];
    unsigned short s_g = lightParams[4];
    unsigned short s_b = lightParams[5];
    switch (mode) {
        case LightMode::l_static:
            PS4.setFlashRate(255, 0);
            break;
        case LightMode::flashing:
            PS4.setFlashRate(127, 127);
            break;
        case LightMode::slow_flashing:
            PS4.setFlashRate(255, 255);
            break;
        case LightMode::fast_flashing:
            PS4.setFlashRate(92, 92);
            break;
        case LightMode::flashing_dual_colors:
            ps4AmbientVariables::timeToChange = (millis() - ps4AmbientVariables::lastlightUpdateTimestamp) > 190;
            if (!ps4AmbientVariables::timeToChange)
                return;
            if (ps4AmbientVariables::alternateController)
                PS4.setLed(f_r, f_g, f_b);
            else
                PS4.setLed(s_r, s_g, s_b);
            ps4AmbientVariables::alternateController = !ps4AmbientVariables::alternateController;
            ps4AmbientVariables::lastlightUpdateTimestamp = millis();
            PS4.setFlashRate(255, 0);
            PS4.sendToController();
            return;
        case LightMode::slow_flashing_dual_colors:
            ps4AmbientVariables::timeToChange = (millis() - ps4AmbientVariables::lastlightUpdateTimestamp) > 450;
            if (!ps4AmbientVariables::timeToChange)
                return;
            if (ps4AmbientVariables::alternateController)
                PS4.setLed(f_r, f_g, f_b);
            else
                PS4.setLed(s_r, s_g, s_b);
            ps4AmbientVariables::alternateController = !ps4AmbientVariables::alternateController;
            ps4AmbientVariables::lastlightUpdateTimestamp = millis();
            PS4.setFlashRate(255, 0);
            PS4.sendToController();
            return;

        default:
            PS4.setFlashRate(255, 0);
            break;
    }
    PS4.setLed(f_r, f_g, f_b);
    PS4.sendToController();
}

void processControllerEvents() {
    // Verifica se o controle está conectado antes de prosseguir com a função
    if (robotData.controllerStatus == ControllerStatus::disconnected)
        return;

    readControllerInputs();

    //-- Configura as luzes do controle conforme a situação do robô - State Machine --//

    // Só envia os comandos para alteração das luzes no intervalo de tempo(ms) determinado abaixo
    if (millis() - ps4AmbientVariables::lastControllerUpdateTimestamp < 50)
        return;

    unsigned short* ptr = (unsigned short*)malloc(6 * sizeof(unsigned short));
    // Controla as configurações de luzes do modo autônomo
    if (robotConfiguration.mode == Mode::Auto) {
        switch (robotData.robotState) {
            case RobotState::ready:
                ptr[0] = 0;
                ptr[1] = 0;
                ptr[2] = 255;
                configController(ptr, LightMode::slow_flashing);
                break;
            case RobotState::starting:
                ptr[0] = 0;
                ptr[1] = 255;
                ptr[2] = 0;
                ptr[3] = 255;
                ptr[4] = 0;
                ptr[5] = 0;
                configController(ptr, LightMode::flashing_dual_colors);
                break;
            case RobotState::stopped:
                ptr[0] = 255;
                ptr[1] = 0;
                ptr[2] = 0;
                configController(ptr, LightMode::l_static);
                break;
            case RobotState::exec_controller:
                ptr[0] = 255;
                ptr[1] = 0;
                ptr[2] = 0;
                ptr[3] = 255;
                ptr[4] = 255;
                ptr[5] = 0;
                configController(ptr, LightMode::flashing_dual_colors);
                break;
            default:
                ptr[0] = 0;
                ptr[1] = 255;
                ptr[2] = 0;
                configController(ptr, LightMode::l_static);
                break;
        }
    }
    if (robotConfiguration.mode == Mode::RC) {
        switch (robotData.robotState) {
            case RobotState::ready:
                ptr[0] = 200;
                ptr[1] = 200;
                ptr[2] = 0;
                configController(ptr, LightMode::slow_flashing);
                break;
            case RobotState::starting:
                ptr[0] = 0;
                ptr[1] = 0;
                ptr[2] = 255;
                ptr[3] = 255;
                ptr[4] = 0;
                ptr[5] = 0;
                configController(ptr, LightMode::flashing_dual_colors);
                break;
            case RobotState::stopped:
                ptr[0] = 255;
                ptr[1] = 0;
                ptr[2] = 0;
                configController(ptr, LightMode::l_static);
                break;
            case RobotState::exec_controller:
                ptr[0] = 0;
                ptr[1] = 0;
                ptr[2] = 255;
                configController(ptr, LightMode::l_static);
                break;
            default:
                ptr[0] = 255;
                ptr[1] = 0;
                ptr[2] = 0;
                ptr[3] = 255;
                ptr[4] = 255;
                ptr[5] = 0;
                configController(ptr, LightMode::flashing_dual_colors);
                break;
        }
    }
    ps4AmbientVariables::lastControllerUpdateTimestamp = millis();
    free(ptr);
}

#endif  // PS4_CONTROLLER_HPP