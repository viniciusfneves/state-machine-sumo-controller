#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../events/events.hpp"
#include "../sensors/edge_sensor/edge_sensor.hpp"
#include "../sensors/opponent_sensor/opponent_sensor.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"
#include "../utilities/messages/messages.hpp"

// Responsável por processar informações e emitir
// eventos dinamicamente para a máquina
void handle_events()
{
    if (timeoutActive)
    {
        if (millis() >= timeoutTime)
        {
            cancelTimeout();
            Core.process_event(Timeout{});
        }
    }
    if (isOpponentDetected()){
        display_message("Opponent Detected");
        Core.process_event(OpponentDetected{});
    }
    if (isEdgeDetected())
    {
        display_message("On Edge");
        Core.process_event(EdgeDetected{});
    }
    else
    {
        Core.process_event(Start{});
    }
}
#endif
