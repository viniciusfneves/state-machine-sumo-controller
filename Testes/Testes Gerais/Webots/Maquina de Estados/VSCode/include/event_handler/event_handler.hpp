#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "../machine/machine.hpp"
#include "../events/events.hpp"
#include <iostream>

void handle_events()
{
    using namespace std;
    cout << robot->getTime() * 1000<< endl;
    if ((long)(robot->getTime() * 1000) % 3200 == 0)
    {
        cout << "SHAZAM CARAIO" << endl;
        Core.process_event(Time{});
    }
};

#endif
