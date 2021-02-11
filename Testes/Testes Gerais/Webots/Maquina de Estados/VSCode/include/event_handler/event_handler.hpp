#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/machine.hpp"
#include "../events/events.hpp"

void handle_events()
{
    Core.process_event(Start{});
    delay(2000);
    Core.process_event(Timeout{});
    delay(2000);
    Core.process_event(Terminate{});
    delay(2000);
    Core.process_event(Reset{});
    delay(500);
};

#endif
