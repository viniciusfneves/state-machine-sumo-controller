#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../events/events.hpp"
#include "../sensors/edge_sensor/edge_sensor.hpp"
#include "../sensors/opponent_sensor/opponent_sensor.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"
#include "../utilities/messages/messages.hpp"

#ifdef SUMO3KG
#include <communications/WiFi/WiFi.hpp>
#endif

// Responsável por processar informações e emitir
// eventos dinamicamente para a máquina
void handle_events()
{
    if (isComAvailable())
    {
    }
    else if (eventOnQueue != Event::None)
    {
        switch (eventOnQueue)
        {
        case Event::Start:
            Core.process_event(Start{});
            break;

        case Event::Terminate:
            Core.process_event(Terminate{});
            break;

        case Event::Reset:
            Core.process_event(Reset{});
            break;

        default:
            break;
        }
        Serial.print("Handled Event :");
        Serial.println(static_cast<int>(eventOnQueue));
        eventOnQueue = Event::None;
    }
    else if (isTimeoutActive())
    {
        if (millis() >= timeoutTime)
        {
            cancelTimeout();
            Core.process_event(Timeout{});
        }
    }
    else if (isOpponentDetected())
    {
        display_message("Opponent Detected");
        Core.process_event(OpponentDetected{});
    }
    else if (isEdgeDetected())
    {
        display_message("On Edge");
        Core.process_event(EdgeDetected{});
    }
    else{
        Core.process_event(None{});
    }
}
#endif
