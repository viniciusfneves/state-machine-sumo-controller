#pragma once
#include <map>

#include "../configuration/specifications.hpp"

// Status de execução das estratégias do robô
enum class RobotState {
    ready,
    starting,
    stopped,
    exec_initial,
    exec_search,
    exec_chase,
    exec_controller
};

struct RobotData {
    // Guarda o estado atual do robô -> Inicializado com stopped
    RobotState robotState = RobotState::stopped;

    // SENSOR DE OPONENTES
    std::map<String, bool> opponentSensorsDetectionArray;
    double                 opError;
    bool                   opDetected;

    // SENSOR DE BORDA
    std::map<String, bool> edgeSensorsDetectionArray;
    bool                   edgeDetected;

    // POTÊNCIA DOS MOTORES
    int motorsPower[2];
};

// Objeto dos dados dinâmicas do robô
RobotData robotData;

/*   ##-----> Funções de retorno dos dados <-----##   */

// Retorna true se um oponente foi ou não detectado por um dos sensores
bool isOpponentDetected() { return robotData.opDetected; }

// Retorna o erro do alinhamento do robô com a detecção do oponente
double getErrorFromOPSensors() { return robotData.opError; }

// Retorna true se uma borda foi detectada ou não
bool isEdgeDetected() { return robotData.edgeDetected; }

// Muda na memória do robô o seu estado de execução atual
void changeRobotState(RobotState state) { robotData.robotState = state; }
