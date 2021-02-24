#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/main_machine.hpp"
#include "../events/events.hpp"
#include "../utilities/timeout_implementation/timeout.hpp"

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
    else
    {
        Core.process_event(Start{});
    }
}
#endif
