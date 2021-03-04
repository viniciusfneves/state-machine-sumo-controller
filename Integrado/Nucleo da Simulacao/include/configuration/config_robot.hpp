#if !defined(CONFIG_ROBOT_HPP)
#define CONFIG_ROBOT_HPP

#include "configuration_object.hpp"

#include <events/events.hpp>

void reConfigureRobotFromComm(){
    String initial_configured;
    String search_configured;
    String chase_configured;

    /*------ Processa os comandos emitidos ------*/

    // Processa as requisições de emissão de eventos
    if (doc.containsKey("event_request"))
    {
        const char *request = doc["event_request"];

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
    if (doc.containsKey("initial"))
    {
        const char *strategy = doc["initial"];
        if (strcmp(strategy, "none") == 0)
        {
            config.initialMove = InitialMove::none;
            initial_configured = "none";
            Serial.println("Initial -> NONE");
        }
        if (strcmp(strategy, "full_frente") == 0)
        {
            config.initialMove = InitialMove::full_frente;
            initial_configured = "full_frente";
            Serial.println("Initial -> FULL FRENTE");
        }
    }

    // Processa as requisições de estratégia de busca
    if (doc.containsKey("search"))
    {
        const char *strategy = doc["search"];
        if (strcmp(strategy, "none") == 0)
        {
            config.search = Search::none;
            search_configured = "none";
            Serial.println("Search -> NONE");
        }
        if (strcmp(strategy, "radar") == 0)
        {
            config.search = Search::radar;
            search_configured = "radar";
            Serial.println("Search -> RADAR");
        }
    }

    // Processa as requisições de estratégia de perseguição
    if (doc.containsKey("chase"))
    {
        const char *strategy = doc["chase"];
        if (strcmp(strategy, "standard") == 0)
        {
            config.chase = Chase::standard;
            chase_configured = "chase";
            Serial.println("Chase -> STANDARD");
        }
    }
}


#endif // CONFIG_ROBOT_HPP
