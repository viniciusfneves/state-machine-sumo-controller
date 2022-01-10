#if !defined(ROBOT_DATA_HPP)
#define ROBOT_DATA_HPP

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
    // --------------------------> IMPORTANTE <-------------------------- //
    // NÃO UTILIZAR ARRAYS DE TAMANHO DINÂMICO!!!
    // - PROBLEMAS AO COMPILAR PARA O AMBIENTE DO ARDUINO UNO
    // - PROBLEMAS NA TELEMETRIA NO AMBIENTE DOS 3KG
    // - PROBLEMAS AO COMPILAR DENTRO DO WEBOTS
    // RESUMINDO: NÃO FUNCIONA EM 2 DOS 3 AMBIENTES PRINCIPAIS E FUNCIONA CAPEGANDA NO OUTRO
    // NÃO USE!!!!
    // Tentar utilizar vetores ao invés disso -> Implementação futura

    // Guarda o estado atual do robô -> Inicializado com stopped
    RobotState robotState = RobotState::stopped;

    // SENSOR DE OPONENTES
    bool opponentSensorsDetectionArray[NUMBER_OF_OPPONENT_SENSORS];
    bool opDetected;
    double opError;

    // SENSOR DE BORDA
    bool edgeSensorsDetectionArray[NUMBER_OF_EDGE_SENSORS];
    bool edgeDetected;

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

#endif  // ROBOT_DATA_HPP
