#pragma once

#include <communications/WiFi/websockets_server/websockets_server.hpp>
#include <communications/data/robot_data_json_encoder.hpp>
#include <configuration/set_configurations.hpp>
#include <pins/pins.hpp>
#include <utilities/calculus/calculus.hpp>

#define TELEMETRY_INTERVAL 32000  // us

namespace telemetry {
    unsigned long lastTelemetryTimestamp = 0UL;
};

// Lida com as requisições feitas ao server websocket
void processWebSocketEvents(void *_) {
    for (;;) {
        wss.loop();
        if (micros() - telemetry::lastTelemetryTimestamp >= TELEMETRY_INTERVAL) {
            broadcastTelemetryData();
            telemetry::lastTelemetryTimestamp = micros();
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

/* --> ENVIAR SOMENTE JSON PARA ESSA FUNÇÃO <-- */
// Responsável por pegar as mensagens do tipo JSON, decodificá-las e atuar corretamente no robô conforme as instruções
void processJsonMessage(String message) {
    StaticJsonDocument<128> jsonMessage;
    DeserializationError    JSONerror = deserializeJson(jsonMessage, message);
    if (JSONerror) {
        Serial.println("(Função processJsonMessage) -> JSON-> Ocorreu um erro ao deserializar a mensagem!");
        return;
    }
    // ! Requisições de configurações da máquina de luta

    // Processa as requisições de emissão de eventos
    if (jsonMessage.containsKey("event_request")) {
        const char *request = jsonMessage["event_request"];

        if (strcmp(request, "start") == 0) {
            addEventToQueue(Event::Start);
        }
        if (strcmp(request, "disengage") == 0) {
            addEventToQueue(Event::Disengage);
        }
        if (strcmp(request, "arm") == 0) {
            addEventToQueue(Event::Arm);
        }
        if (strcmp(request, "dump") == 0) {
            broadcastRobotInfos();
            broadcastRobotConfiguration();
        }
    }
    // Processa as requisições de alteração de modo de operação
    if (jsonMessage.containsKey("mode")) {
        const char *strategy = jsonMessage["mode"];

        if (strcmp(strategy, "auto") == 0) {
            setMode(Mode::Auto);
        }
        if (strcmp(strategy, "rc") == 0) {
            setMode(Mode::RC);
        }
    }

    // Processa as requisições de alteração da estratégia inicial
    if (jsonMessage.containsKey("initial")) {
        const char *strategy = jsonMessage["initial"];

        if (strcmp(strategy, "none") == 0) {
            setInitialStrategy(InitialMove::none);
        }
        if (strcmp(strategy, "full_frente") == 0) {
            setInitialStrategy(InitialMove::full_frente);
        }
        if (strcmp(strategy, "zig_zag") == 0) {
            setInitialStrategy(InitialMove::zig_zag);
        }
        if (strcmp(strategy, "arco") == 0) {
            setInitialStrategy(InitialMove::arco);
        }
    }

    // Processa as requisições de alteração da estratégia de busca
    if (jsonMessage.containsKey("search")) {
        const char *strategy = jsonMessage["search"];

        if (strcmp(strategy, "none") == 0) {
            setSearchStrategy(Search::none);
        }
        if (strcmp(strategy, "radar") == 0) {
            setSearchStrategy(Search::radar);
        }
        if (strcmp(strategy, "teco") == 0) {
            setSearchStrategy(Search::teco);
        }
    }

    // Processa as requisições de alteração da estratégia de perseguição
    if (jsonMessage.containsKey("chase")) {
        const char *strategy = jsonMessage["chase"];

        if (strcmp(strategy, "standard") == 0) {
            setChaseStrategy(Chase::standard);
        }
    }

    // Processa as requisições de alteração do comando do robô no modo RC
    if (jsonMessage.containsKey("ctrl_type")) {
        const char *config = jsonMessage["ctrl_type"];

        if (strcmp(config, "bt_ps4") == 0) {
            setCtrlType(Commander::bt_ps4);
        }
        if (strcmp(config, "radio") == 0) {
            setCtrlType(Commander::radio);
        }
    }

    // Processa as requisições de alteração do map de comandos do controle RC
    if (jsonMessage.containsKey("ctrl_map")) {
        const char *config = jsonMessage["ctrl_map"];

        if (strcmp(config, "game_standard") == 0) {
            setCtrlMapping(CommandMap::game_standard);
        }
        if (strcmp(config, "rc_standard") == 0) {
            setCtrlMapping(CommandMap::rc_standard);
        }
        if (strcmp(config, "rc_inverted") == 0) {
            setCtrlMapping(CommandMap::rc_inverted);
        }
    }

    // Processa as requisições de alteração dos filtros nos comandos do controle
    if (jsonMessage.containsKey("ctrl_filter")) {
        const char *config = jsonMessage["ctrl_filter"];

        if (strcmp(config, "linear") == 0) {
            setCtrlFilter(CommandFilter::linear);
        }
        if (strcmp(config, "quadratic") == 0) {
            setCtrlFilter(CommandFilter::quadratic);
        }
        if (strcmp(config, "cubic") == 0) {
            setCtrlFilter(CommandFilter::cubic);
        }
    }

    // Processa pedido de alteração do tempo para início do luta
    if (jsonMessage.containsKey("start_time")) {
        setStartTime(jsonMessage["start_time"]);
    }

    // ! Requisições de configurações de parâmetros globais

    // Processa pedido de alteração do bias de controle de tempo de rotateRobot
    if (jsonMessage.containsKey("rotate_angle_bias")) {
        setRotateRobotAngleBias(jsonMessage["rotate_angle_bias"]);
    }

    // Processa pedido de alteração do bias de controle de tempo de rotateRobot
    if (jsonMessage.containsKey("rotate_speed_bias")) {
        setRotateRobotSpeedBias(jsonMessage["rotate_speed_bias"]);
    }

    // Processa pedido de alteração da velocidade máxima permitida para o robô
    if (jsonMessage.containsKey("max_speed")) {
        setMaxSpeed(jsonMessage["max_speed"]);
    }

    if (jsonMessage.containsKey("invert_op_sensors")) {
        setInvertOpSensorReading(jsonMessage["invert_op_sensors"]);
    }

    if (jsonMessage.containsKey("op_sensors_weight")) {
        for (auto sensor = pins::opponentsSensors::sensors.begin(); sensor != pins::opponentsSensors::sensors.end(); sensor++) {
            if (jsonMessage["op_sensors_weight"].containsKey(sensor->first)) {
                setOpSensorWeight(sensor->first, jsonMessage["op_sensors_weight"][sensor->first]);
            }
        }
    }

    // Processa pedido de alteração das constantes do pid
    if (jsonMessage.containsKey("pid")) {
        setPIDConstants(jsonMessage["pid"]["kp"], jsonMessage["pid"]["ki"], jsonMessage["pid"]["kd"]);
    }

    // ! Requisições de configurações de parâmetros específicos de estratégias

    // Processa pedido de alteração da velocidade de rotação do radar
    if (jsonMessage.containsKey("radar_speed")) {
        setRadarSpeed(jsonMessage["radar_speed"]);
    }

    // Processa pedido de alteração do tempo de execução do arco
    if (jsonMessage.containsKey("arc_timeout")) {
        setArcTimeout(jsonMessage["arc_timeout"]);
    }

    // Processa pedido de alteração da velocidade angular do arco
    if (jsonMessage.containsKey("arc_angular_speed")) {
        setArcAngularSpeed(jsonMessage["arc_angular_speed"]);
    }

    // Processa pedido de alteração da angulação do arco
    if (jsonMessage.containsKey("arc_rot_initial_angle")) {
        setAngle(jsonMessage["arc_rot_initial_angle"]);
    }

    // Processa pedido de alteração da velocidade máx em perseguição
    if (jsonMessage.containsKey("max_angular_speed_in_chase")) {
        setMaxAngularSpeedInChase(jsonMessage["max_angular_speed_in_chase"]);
    }
}

/* --> Enviar somente JSON <-- */
// Lida com os dados recebidos pelo protocolo WebSocket
void handleWSEvent(uint8_t client_id, WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        // Caso haja um erro no recebimento de uma mensagem do cliente
        case WStype_ERROR:
            break;
        // Caso uma nova conexão seja aceita
        case WStype_CONNECTED:
            broadcastRobotInfos();
            broadcastRobotConfiguration();
            break;
        // Caso a mensagem seja do tipo text
        case WStype_TEXT:
            processJsonMessage(String((char *)payload));
            break;
        default:
            break;
    }
}

// Inicia o serviço websocket
void initWebSocketsServer() {
    wss.begin();

    // Configura qual função é executada a cada evento recebido pelo WebSocket
    wss.onEvent(handleWSEvent);
    xTaskCreate(processWebSocketEvents, "WSServer", 1024 * 4, NULL, 1, NULL);
}
