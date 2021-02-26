#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../events/events.hpp"
#include "../sensors/edge_sensor/edge_sensor.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"
#include "../utilities/messages/messages.hpp"

// Responsável por processar informações e emitir
// eventos dinamicamente para a máquina
void handle_events()
{
    if (isOnEdge())
    {
        display_message("On Edge");
        Core.process_event(BorderDetected{});
    }
    if (timeoutActive)
    {
        if (millis() >= timeoutTime)
        {
            cancelTimeout();
            Core.process_event(Timeout{});
        }
    }
    else
    {
        Core.process_event(Start{});
    }
}
#endif
