#if !defined(INCOMING_DATA_HPP)
#define INCOMING_DATA_HPP

#include <ArduinoJson.h>

#include <configuration/configurations.hpp>
#include <dynamic_data/dynamic_data.hpp>
#include <event_handler/circular_buffer.hpp>
#include <events/events.hpp>

/* --> ENVIAR SOMENTE JSON PARA ESSA FUNÇÃO <-- */
// Responsável por pegar as mensagens do tipo JSON, decodificá-las e atuar corretamente no robô conforme as instruções
void processJsonMessage(String message) {
    StaticJsonDocument<128> jsonMessage;
    DeserializationError JSONerror = deserializeJson(jsonMessage, message);
    if (JSONerror) {
        Serial.println("(Função processJsonMessage) -> JSON-> Ocorreu um erro ao deserializar a mensagem!");
        return;
    }

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
    }

    // Processa pedido de alteração do tempo para início do luta
    if (jsonMessage.containsKey("start_time")) {
        setStartTime(jsonMessage["start_time"]);
    }

    // Processa pedido de alteração da velocidade máxima permitida para o robô
    if (jsonMessage.containsKey("max_speed")) {
        setMaxSpeed(jsonMessage["max_speed"]);
    }

    // Processa pedido de alteração das constantes do pid
    if (jsonMessage.containsKey("pid")) {
        changePIDSettings(jsonMessage["pid"]["kp"], jsonMessage["pid"]["ki"], jsonMessage["pid"]["kd"]);
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
    }

    // Processa as requisições de alteração da estratégia de perseguição
    if (jsonMessage.containsKey("chase")) {
        const char *strategy = jsonMessage["chase"];

        if (strcmp(strategy, "standard") == 0) {
            setChaseStrategy(Chase::standard);
        }
    }

    // Caso receba comandos de controle, atua nos motores se o modo RC estiver ativo
    if (jsonMessage.containsKey("controller") && robotConfiguration.mode == Mode::RC) {
        robotData.controllerInputs[Input::linearSpeed] = jsonMessage["controller"]["linearSpeed"];
        robotData.controllerInputs[Input::angularSpeed] = jsonMessage["controller"]["angularSpeed"];
        addEventToQueue(Event::Controller);
    }
};

#endif  // DYNAMIC_DATA_HPP
