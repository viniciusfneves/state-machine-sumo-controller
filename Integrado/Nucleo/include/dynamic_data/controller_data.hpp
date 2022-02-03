#pragma once

using std::vector;

// Status de conexão do controle de PS4
enum class ControllerStatus {
    connected,
    disconnected
};

// Enumera os inputs recebidos pelo controle.
// Define a ordem de armazenamento desses inputs no array que guarda essas informações
enum Input {
    linearSpeed,
    angularSpeed,
    length
};

enum class Commander {
    bt_ps4,
    radio
};

enum class CommandMap {
    rc_standard,
    rc_inverted,
    game_standard
};

enum class CommandFilter {
    linear,
    quadratic,
    cubic
};

vector<String> ctrl_types     = {"bt_ps4", "radio"};
vector<String> ctrl_maps      = {"game_standard", "rc_standard", "rc_inverted"};
vector<String> ctrl_filters   = {"linear", "quadratic", "cubic"};

// Informações e leituras do Controle de PS4
struct ControllerData {
    ControllerStatus controllerStatus = ControllerStatus::disconnected;
    Commander commander = Commander::bt_ps4;
    CommandMap mapSettings = CommandMap::game_standard;
    CommandFilter filterSettings = CommandFilter::quadratic;
    double controllerInputs[Input::length];  // Segue a ordem do enum Input
    uint8_t battery = 0;
    bool isCharging = false;

    bool isControllerConnected() { return controllerStatus == ControllerStatus::connected ? true : false; }
};

ControllerData controllerData;
