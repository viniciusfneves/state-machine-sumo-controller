#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <machine/main_machine.hpp>
#include <events/events.hpp>
#include <utilities/timeout_implementation/timeout.hpp>

void handle_events()
{
    if (timeoutActive)
    {
        if (millis() >= timeoutTime)
        {
            Core.process_event(Timeout{});
        };
    }
    else
    {
        Core.process_event(Start{});
    };
};
#endif
