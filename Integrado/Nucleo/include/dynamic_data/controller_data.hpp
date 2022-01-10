#ifndef CONTROLLER_DATA_HPP
#define CONTROLLER_DATA_HPP

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

enum class CommandMapping {
    linear,
    cubic,
    rc_controller_standard
};

// Informações e leituras do Controle de PS4
struct ControllerData {
    ControllerStatus controllerStatus = ControllerStatus::disconnected;
    CommandMapping mapSettings = CommandMapping::cubic;
    double controllerInputs[Input::length];  // Segue a ordem do enum Input
    unsigned short battery = 0;
    bool isCharging = false;

    bool isControllerConnected() { return controllerStatus == ControllerStatus::connected ? true : false; }
};

ControllerData controllerData;

#endif  // CONTROLLER_DATA_HPP
