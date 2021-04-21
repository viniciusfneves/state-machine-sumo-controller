#if !defined(DYNAMIC_DATA_HPP)
#define DYNAMIC_DATA_HPP

#include "../configuration/specifications.hpp"

struct DynamicData
{
    // --------------------------> IMPORTANTE <-------------------------- //
    // NÃO UTILIZAR ARRAYS DE TAMANHO DINÂMICO!!!
    // - PROBLEMAS AO COMPILAR PARA O AMBIENTE DO ARDUINO UNO
    // - PROBLEMAS NA TELEMETRIA NO AMBIENTE DOS 3KG
    // - PROBLEMAS AO COMPILAR DENTRO DO WEBOTS
    // RESUMINDO: NÃO FUNCIONA EM 2 DOS 3 AMBIENTES PRINCIPAIS E FUNCIONA CAPEGANDA NO OUTRO
    // NÃO USE!!!!

    // SENSOR DE OPONENTES
    bool opponentSensorDetectionArray[NUMBER_OF_OPPONENT_SENSORS];
    bool opDetected;
    double opError;

    // SENSOR DE BORDA
    bool edgeSensorDetectionArray[NUMBER_OF_EDGE_SENSORS];
    bool edgeDetected;

    // POTÊNCIA DOS MOTORES
    //int motorsPower[];

    // INPUTS DO CONTROLE -> MODO RC
    double controllerInputs[NUMBER_OF_CONTROLLER_CHANNELS]; // [0] -> linearSpeed, [1] -> angularSpeed
};

DynamicData robotData;

// Funções para pegar leituras dos sensores de oponente

// Retorna true se um oponente foi ou não detectado por um dos sensores
bool isOpponentDetected() { return robotData.opDetected; }
// Retorna o erro calculado de acordo com o peso de cada sensor de oponente que detectou um objeto
double getErrorFromOPSensors() { return robotData.opError; }

// Funções para pegar leituras dos sensores de borda

// Retorna true se uma borda foi detectada ou não
bool isEdgeDetected() { return robotData.edgeDetected; }

#endif // DYNAMIC_DATA_HPP
