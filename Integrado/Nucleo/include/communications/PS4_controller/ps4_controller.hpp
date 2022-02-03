#pragma once

#define CONTROLLER_MAC_ADDRESS "00:1a:7d:da:71:03"
#define MAX_BREATH_BRIGHTNESS 200
#define BREATH_COLOR_DECAY 20
#define CTRL_UPDATE_INTERVAL 32000  //us

#define SET_UNIQUE_COLOR(_r, _g, _b)          \
    ps4LightCtrl::r = _r;                     \
    ps4LightCtrl::g = _g;                     \
    ps4LightCtrl::b = _b;                     \
    ps4LightCtrl::r_var = BREATH_COLOR_DECAY; \
    ps4LightCtrl::g_var = BREATH_COLOR_DECAY; \
    ps4LightCtrl::b_var = BREATH_COLOR_DECAY

#define SET_DUAL_COLORS(r1, g1, b1, r2, g2, b2) \
    ps4LightCtrl::r = r1;                       \
    ps4LightCtrl::g = g1;                       \
    ps4LightCtrl::b = b1;                       \
    ps4LightCtrl::r_buf = r2;                   \
    ps4LightCtrl::g_buf = g2;                   \
    ps4LightCtrl::b_buf = b2;                   \
    ps4LightCtrl::r_var = BREATH_COLOR_DECAY;   \
    ps4LightCtrl::g_var = BREATH_COLOR_DECAY;   \
    ps4LightCtrl::b_var = BREATH_COLOR_DECAY

#define SET_BREATHING_COLOR(_r, _g, _b) \
    ps4LightCtrl::r_buf = _r;           \
    ps4LightCtrl::g_buf = _g;           \
    ps4LightCtrl::b_buf = _b

// time define o tempo(us) no qual as luzes devem alternar
#define DUAL_COLOR_FLASHING_LIGHT_HANDLER(time)                                               \
    ps4LightCtrl::timeToChange = (micros() - ps4Timestamps::lastlightUpdateTimestamp) > time; \
    if (!ps4LightCtrl::timeToChange)                                                          \
        return;                                                                               \
    if (ps4LightCtrl::switchController)                                                       \
        PS4.setLed(ps4LightCtrl::r, ps4LightCtrl::g, ps4LightCtrl::b);                        \
    else                                                                                      \
        PS4.setLed(ps4LightCtrl::r_buf, ps4LightCtrl::g_buf, ps4LightCtrl::b_buf);            \
    ps4LightCtrl::switchController ^= 1;                                                      \
    ps4Timestamps::lastlightUpdateTimestamp = micros();                                       \
    PS4.setFlashRate(255, 0);                                                                 \
    PS4.sendToController();                                                                   \
    return

// timing define a velocidade do breathing, sendo um valor mais baixo, o mais rápido
#define BREATHING_LIGHT_HANDLER(timing)                                                                                                                                                                                  \
    if (((ps4LightCtrl::r == 0) * (ps4LightCtrl::g == 0) * (ps4LightCtrl::b == 0))) {                                                                                                                                    \
        ps4LightCtrl::r_var = ps4LightCtrl::r_buf / timing;                                                                                                                                                              \
        ps4LightCtrl::g_var = ps4LightCtrl::g_buf / timing;                                                                                                                                                              \
        ps4LightCtrl::b_var = ps4LightCtrl::b_buf / timing;                                                                                                                                                              \
    }                                                                                                                                                                                                                    \
    if (ps4LightCtrl::switchController) {                                                                                                                                                                                \
        ps4LightCtrl::r += ps4LightCtrl::r_var;                                                                                                                                                                          \
        ps4LightCtrl::g += ps4LightCtrl::g_var;                                                                                                                                                                          \
        ps4LightCtrl::b += ps4LightCtrl::b_var;                                                                                                                                                                          \
        if (((ps4LightCtrl::r + ps4LightCtrl::r_var) > MAX_BREATH_BRIGHTNESS) + ((ps4LightCtrl::g + ps4LightCtrl::g_var) > MAX_BREATH_BRIGHTNESS) + ((ps4LightCtrl::b + ps4LightCtrl::b_var) > MAX_BREATH_BRIGHTNESS)) { \
            ps4LightCtrl::switchController ^= 1;                                                                                                                                                                         \
        }                                                                                                                                                                                                                \
    } else {                                                                                                                                                                                                             \
        ps4LightCtrl::r -= ps4LightCtrl::r_var;                                                                                                                                                                          \
        ps4LightCtrl::g -= ps4LightCtrl::g_var;                                                                                                                                                                          \
        ps4LightCtrl::b -= ps4LightCtrl::b_var;                                                                                                                                                                          \
        if (((ps4LightCtrl::r - ps4LightCtrl::r_var) <= 0) * ((ps4LightCtrl::g - ps4LightCtrl::g_var) <= 0) * ((ps4LightCtrl::b - ps4LightCtrl::b_var) <= 0)) {                                                          \
            ps4LightCtrl::switchController ^= 1;                                                                                                                                                                         \
            SET_UNIQUE_COLOR(0, 0, 0);                                                                                                                                                                                   \
        }                                                                                                                                                                                                                \
    }                                                                                                                                                                                                                    \
    ps4LightCtrl::r = constrain(ps4LightCtrl::r, 0, MAX_BREATH_BRIGHTNESS);                                                                                                                                              \
    ps4LightCtrl::g = constrain(ps4LightCtrl::g, 0, MAX_BREATH_BRIGHTNESS);                                                                                                                                              \
    ps4LightCtrl::b = constrain(ps4LightCtrl::b, 0, MAX_BREATH_BRIGHTNESS);                                                                                                                                              \
    PS4.setLed(ps4LightCtrl::r, ps4LightCtrl::g, ps4LightCtrl::b);                                                                                                                                                       \
    PS4.setFlashRate(255, 0);                                                                                                                                                                                            \
    PS4.sendToController();                                                                                                                                                                                              \
    return

#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#include <configuration/set_configurations.hpp>
#include <dynamic_data/controller_data.hpp>
#include <utilities/calculus/calculus.hpp>

namespace ps4Timestamps {
unsigned long lastControllerUpdateTimestamp = 0UL;
unsigned long lastlightUpdateTimestamp = 0UL;
}  // namespace ps4Timestamps

namespace ps4LightCtrl {
int16_t r_buf, g_buf, b_buf;
int16_t r_var, g_var, b_var;
int16_t r, g, b;
bool timeToChange = false;
bool switchController = true;
}  // namespace ps4LightCtrl

enum class LightMode {
    l_static,
    flashing,
    fast_flashing,
    slow_flashing,
    flashing_dual_colors,
    slow_flashing_dual_colors,
    breathing
};

enum class Vibration {
    none,
    weak,
    strong
};

void initController() {
    PS4.begin(CONTROLLER_MAC_ADDRESS);
    PS4.attachOnConnect([] {
        controllerData.controllerStatus = ControllerStatus::connected;
    });
    PS4.attachOnDisconnect([] {
        controllerData.controllerStatus = ControllerStatus::disconnected;
    });
}

// Lê os comandos do controle e atua na máquina(robô) conforme necessário
void readControllerInputs() {
    controllerData.isCharging = PS4.Charging();
    controllerData.battery = PS4.Battery();
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
    if (controllerData.commander != Commander::bt_ps4)
        return;

    int _trigger, _stick, _pedal, _wheel;
    double _linear, _angular;
    switch (controllerData.mapSettings) {
        case CommandMap::game_standard:
            _trigger = PS4.R2Value() - PS4.L2Value();
            _stick = PS4.LStickX();
            _linear = map_double(_trigger, -255, 255, -1, 1);
            _angular = map_double(_stick, -128, 127, -1, 1);

            if (abs(_angular) < 0.07)
                _angular = 0;
            break;

        case CommandMap::rc_standard:
            _pedal = PS4.LStickY();
            _wheel = PS4.RStickX();
            _linear = map_double(_pedal, -128, 127, -1, 1);
            _angular = map_double(_wheel, -128, 127, -1, 1);

            if (abs(_angular) < 0.07)
                _angular = 0;
            if (abs(_linear) < 0.07)
                _linear = 0;
            break;

        case CommandMap::rc_inverted:
            _pedal = PS4.RStickY();
            _wheel = PS4.LStickX();
            _linear = map_double(_pedal, -128, 127, -1, 1);
            _angular = map_double(_wheel, -128, 127, -1, 1);

            if (abs(_angular) < 0.07)
                _angular = 0;
            if (abs(_linear) < 0.07)
                _linear = 0;
            break;

        default:
            _angular = 0;
            _linear = 0;
    }

    switch (controllerData.filterSettings) {
        case CommandFilter::linear:
            controllerData.controllerInputs[Input::linearSpeed] = _linear;
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
            controllerData.controllerInputs[Input::linearSpeed] = pow(_linear, 3);
            controllerData.controllerInputs[Input::angularSpeed] = pow(_angular, 3);
            break;

        default:
            controllerData.controllerInputs[Input::linearSpeed] = _linear;
            controllerData.controllerInputs[Input::angularSpeed] = _angular;
            break;
    }

    if (robotConfiguration.mode == Mode::RC) {
        addEventToQueue(Event::Controller);
    }
}

void configController(const LightMode& mode, const Vibration vibro = Vibration::none) {
    switch (vibro) {
        case Vibration::none:
            PS4.setRumble(0, 0);
            break;

        case Vibration::weak:
            PS4.setRumble(92, 127);
            break;

        case Vibration::strong:
            PS4.setRumble(170, 255);
            break;
    }
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
            DUAL_COLOR_FLASHING_LIGHT_HANDLER(190000);

        case LightMode::slow_flashing_dual_colors:
            DUAL_COLOR_FLASHING_LIGHT_HANDLER(450000);

        case LightMode::breathing:
            BREATHING_LIGHT_HANDLER(80);

        default:
            PS4.setFlashRate(255, 0);
            break;
    }
    PS4.setLed(ps4LightCtrl::r, ps4LightCtrl::g, ps4LightCtrl::b);
    PS4.sendToController();
}

void processControllerEvents() {
    // Verifica se o controle está conectado antes de prosseguir com a função
    if (!controllerData.isControllerConnected())
        return;

    readControllerInputs();

    //-- Configura as luzes do controle conforme a situação do robô - State Machine --//

    if (micros() - ps4Timestamps::lastControllerUpdateTimestamp < CTRL_UPDATE_INTERVAL)
        return;
    ps4Timestamps::lastControllerUpdateTimestamp = micros();

    if (controllerData.isCharging && robotData.robotState == RobotState::stopped) {
        SET_BREATHING_COLOR(255, 0, 0);
        configController(LightMode::breathing);
        return;
    }

    // Controla as configurações de luzes do modo autônomo
    if (robotConfiguration.mode == Mode::Auto) {
        switch (robotData.robotState) {
            case RobotState::ready:
                SET_UNIQUE_COLOR(0, 0, 255);
                configController(LightMode::slow_flashing);
                break;

            case RobotState::starting:
                SET_DUAL_COLORS(0, 255, 0, 255, 0, 0);
                configController(LightMode::flashing_dual_colors);
                break;

            case RobotState::stopped:
                SET_UNIQUE_COLOR(255, 0, 0);
                configController(LightMode::l_static);
                break;

            case RobotState::exec_controller:
                SET_DUAL_COLORS(255, 0, 0, 255, 255, 0);
                configController(LightMode::flashing_dual_colors, Vibration::weak);
                break;

            default:
                SET_UNIQUE_COLOR(0, 255, 0);
                configController(LightMode::l_static);
                break;
        }
    }
    if (robotConfiguration.mode == Mode::RC) {
        switch (robotData.robotState) {
            case RobotState::ready:
                SET_UNIQUE_COLOR(200, 200, 0);
                configController(LightMode::slow_flashing);
                break;

            case RobotState::starting:
                SET_DUAL_COLORS(0, 0, 255, 255, 0, 0);
                configController(LightMode::flashing_dual_colors);
                break;

            case RobotState::stopped:
                SET_UNIQUE_COLOR(255, 0, 0);
                configController(LightMode::l_static);
                break;

            case RobotState::exec_controller:
                SET_UNIQUE_COLOR(0, 0, 255);
                configController(LightMode::l_static);
                break;

            default:
                SET_DUAL_COLORS(255, 0, 0, 255, 255, 0);
                configController(LightMode::flashing_dual_colors, Vibration::weak);
                break;
        }
    }
}