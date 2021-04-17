#if !defined(INCOMING_DATA_HPP)
#define INCOMING_DATA_HPP

#include <ArduinoJson.h>
#include <configuration/configurations.hpp>
#include <events/events.hpp>
#include <event_handler/circular_buffer.hpp>

void processMessages(String message)
{
    StaticJsonDocument<128> jsonMessage;
    DeserializationError JSONerror = deserializeJson(jsonMessage, message);
    if (JSONerror)
    {
        Serial.println("JSON -> Ocorreu um erro ao deserializar a mensagem");
        return;
    }
    if (jsonMessage.containsKey("event_request"))
    {
        const char *request = jsonMessage["event_request"];

        if (strcmp(request, "start") == 0)
        {
            addEventToQueue(Event::Start);
        }
        if (strcmp(request, "terminate") == 0)
        {
            addEventToQueue(Event::Terminate);
        }
        if (strcmp(request, "reset") == 0)
        {
            addEventToQueue(Event::Reset);
        }
    }

    // Processa as requisições de estratégia inicial
    if (jsonMessage.containsKey("initial"))
    {
        const char *strategy = jsonMessage["initial"];

        if (strcmp(strategy, "none") == 0)
        {
            setInitialStrategy(InitialMove::none);
        }
        if (strcmp(strategy, "full_frente") == 0)
        {
            setInitialStrategy(InitialMove::full_frente);
        }
        if (strcmp(strategy, "zig_zag") == 0)
        {
            setInitialStrategy(InitialMove::zig_zag);
        }
    }

    // Processa as requisições de estratégia de busca
    if (jsonMessage.containsKey("search"))
    {
        const char *strategy = jsonMessage["search"];

        if (strcmp(strategy, "none") == 0)
        {
            setSearchStrategy(Search::none);
        }
        if (strcmp(strategy, "radar") == 0)
        {
            setSearchStrategy(Search::radar);
        }
    }

    // Processa as requisições de estratégia de perseguição
    if (jsonMessage.containsKey("chase"))
    {
        const char *strategy = jsonMessage["chase"];

        if (strcmp(strategy, "standard") == 0)
        {
            setChaseStrategy(Chase::standard);
        }
    }
    addEventToQueue(Event::SendRobotConfig);

    if (jsonMessage.containsKey("controller") && robotConfiguration.mode == Mode::RC)
    {
        double linearSpeed = jsonMessage["controller"]["linearSpeed"];
        double angularSpeed = jsonMessage["controller"]["angularSpeed"];
        Serial.print("Linear: ");
        Serial.print(linearSpeed);
        Serial.print("  Angular: ");
        Serial.println(angularSpeed);
    }
};

#endif // DYNAMIC_DATA_HPP
