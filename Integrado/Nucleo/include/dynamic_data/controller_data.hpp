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
    game_standard,
    nog
};

enum class CommandFilter {
    linear,
    quadratic,
    cubic
};

vector<String> ctrlTypes   = {"bt_ps4", "radio"};
vector<String> ctrlMaps    = {"game_standard", "rc_standard", "rc_inverted", "nog"};
vector<String> ctrlFilters = {"linear", "quadratic", "cubic"};

// Informações e leituras do Controle de PS4
struct ControllerData {
    ControllerStatus controllerStatus = ControllerStatus::disconnected;
    Commander        commander        = Commander::bt_ps4;
    CommandMap       mapSettings      = CommandMap::game_standard;
    CommandFilter    filterSettings   = CommandFilter::quadratic;
    uint8_t          battery          = 0;
    bool             isCharging       = false;
    double           controllerInputs[Input::length];  // Segue a ordem do enum Input

    bool isControllerConnected() { return controllerStatus == ControllerStatus::connected ? true : false; }
};

ControllerData controllerData;

SemaphoreHandle_t xCtrlDataSemaphore = xSemaphoreCreateMutex();
