#if !defined(DYNAMIC_DATA_HPP)
#define DYNAMIC_DATA_HPP

struct DynamicData
{
    // SENSOR DE OPONENTES
    bool opDetected;
    double opError;

    // SENSOR DE BORDA
    bool edgeDetected;

    // POTÊNCIA DOS MOTORES
    //int motorsPower[];

    // --------------------------> IMPORTANTE <-------------------------- //
    // ARRAYS DINÂMICOS PRECISAM SER OS ÚLTIMOS DENTRO DA STRUCT, SE NÃO O AMBIENTE DOS MINIS (Arduino Uno) APRESENTA ERRO
    // O AMBIENTE DOS 3KG APRESENTA UM WARNING PQ O ARRAY É DINÂMICO, DESDE QUE NÃO SE TENTE ACESSAR UM INDEX QUE NÃO EXISTA, O PROGRAMA RODARÁ NORMALMENTE

    // Array de detecção de oponentes
    bool opponentSensorDetectionArray[];
    // Array de detecção de borda
    bool edgeSensorDetectionArray[];
    // INPUTS DO CONTROLE -> MODO RC
    double controllerInputs[]; // [0] -> linearSpeed, [1] -> angularSpeed
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
