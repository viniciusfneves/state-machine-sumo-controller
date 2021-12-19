#if !defined(DYNAMIC_DATA_HPP)
#define DYNAMIC_DATA_HPP

#include "../configuration/specifications.hpp"

// Status de execução das estratégias do robô
enum RobotState {
    ready,
    starting,
    stopped,
    exec_initial,
    exec_search,
    exec_chase
};

// Enumera os inputs recebidos pelo controle.
// Define a ordem de armazenamento desses inputs no array que guarda essas informações
enum Input {
    linearSpeed,
    angularSpeed
};

struct DynamicData {
    // --------------------------> IMPORTANTE <-------------------------- //
    // NÃO UTILIZAR ARRAYS DE TAMANHO DINÂMICO!!!
    // - PROBLEMAS AO COMPILAR PARA O AMBIENTE DO ARDUINO UNO
    // - PROBLEMAS NA TELEMETRIA NO AMBIENTE DOS 3KG
    // - PROBLEMAS AO COMPILAR DENTRO DO WEBOTS
    // RESUMINDO: NÃO FUNCIONA EM 2 DOS 3 AMBIENTES PRINCIPAIS E FUNCIONA CAPEGANDA NO OUTRO
    // NÃO USE!!!!

    // Guarda o estado atual do robô -> Inicializado com stopped
    RobotState robotState = RobotState::stopped;

    //MÓDULO START
    bool lastState = false;
    bool currentState = false;

    // SENSOR DE OPONENTES
    bool opponentSensorsDetectionArray[NUMBER_OF_OPPONENT_SENSORS];
    bool opDetected;
    double opError;

    // SENSOR DE BORDA
    bool edgeSensorsDetectionArray[NUMBER_OF_EDGE_SENSORS];
    bool edgeDetected;

    // POTÊNCIA DOS MOTORES
    int motorsPower[2];

    // INPUTS DO CONTROLE -> MODO RC
    double controllerInputs[NUMBER_OF_CONTROLLER_CHANNELS];  // Segue a ordem do enum Input

    // CONSTANTES DE TEMPO
    long double tempoRadar;  // Tempo em millis() que foi acionado o radar
};

// Objeto dos dados dinâmicas do robô
DynamicData robotData;

/*   ##-----> Funções de retorno dos dados <-----##   */

// Retorna true se um oponente foi ou não detectado por um dos sensores
bool isOpponentDetected() { return robotData.opDetected; }

// Retorna o erro do alinhamento do robô com a detecção do oponente
double getErrorFromOPSensors() { return robotData.opError; }

// Retorna true se uma borda foi detectada ou não
bool isEdgeDetected() { return robotData.edgeDetected; }

// Muda na memória do robô o seu estado de execução atual
void changeRobotState(RobotState state) { robotData.robotState = state; }

#endif  // DYNAMIC_DATA_HPP
