#if !defined(DYNAMIC_DATA_HPP)
#define DYNAMIC_DATA_HPP

#include <ArduinoJson.h>
#include <events/events.hpp>
#include <configuration/configurations.hpp>

void processMessages(String message)
{
    StaticJsonDocument<512> jsonMessage;
    DeserializationError JSONerror = deserializeJson(jsonMessage, message);
    if (JSONerror){
        Serial.println("JSON -> Ocorreu um erro ao deserializar a mensagem");
    }
    if (jsonMessage.containsKey("event_request"))
    {
        const char *request = jsonMessage["event_request"];

        if (strcmp(request, "start") == 0)
        {
            Serial.println("START TO QUEUE");
            addEventToQueue(Event::Start);
        }
        if (strcmp(request, "terminate") == 0)
        {
            Serial.println("TERMINATE TO QUEUE");
            addEventToQueue(Event::Terminate);
        }
        if (strcmp(request, "reset") == 0)
        {
            Serial.println("RESET TO QUEUE");
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
            Serial.println("Initial -> NONE");
        }
        if (strcmp(strategy, "full_frente") == 0)
        {
            setInitialStrategy(InitialMove::full_frente);
            Serial.println("Initial -> FULL FRENTE");
        }
        if (strcmp(strategy, "zig_zag") == 0)
        {
            setInitialStrategy(InitialMove::zig_zag);
            Serial.println("Initial -> ZIGZAG");
        }
    }

    // Processa as requisições de estratégia de busca
    if (jsonMessage.containsKey("search"))
    {
        const char *strategy = jsonMessage["search"];
        if (strcmp(strategy, "none") == 0)
        {
            setSearchStrategy(Search::none);
            Serial.println("Search -> NONE");
        }
        if (strcmp(strategy, "radar") == 0)
        {
            setSearchStrategy(Search::radar);
            Serial.println("Search -> RADAR");
        }
    }

    // Processa as requisições de estratégia de perseguição
    if (jsonMessage.containsKey("chase"))
    {
        const char *strategy = jsonMessage["chase"];
        if (strcmp(strategy, "standard") == 0)
        {
            setChaseStrategy(Chase::standard);
            Serial.println("Chase -> STANDARD");
        }
    }
};

#endif // DYNAMIC_DATA_HPP
