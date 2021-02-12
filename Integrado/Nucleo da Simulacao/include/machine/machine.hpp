#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <sml.hpp>
#include <events/events.hpp>
#include <selectors/initial_move_selector/initial_move_selector.hpp>
#include <selectors/search_selector/search_selector.hpp>
//#include <Arduino.h>

namespace sml = boost::sml;

//ACTIONS


//MAIN MACHINE
struct machine
{
    struct FightState
    {
        auto operator()() const
        {
            using namespace sml;
            return make_transition_table(
                *"entry"_s = state<InitialMoveSelector>, 
                state<InitialMoveSelector>  +         event<Timeout>                                      =          state<SearchSelector>);
        }
    };

public:
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"initial"_s = "Configuration"_s,

            "Configuration"_s               +         event<Start>                                       =           "StartClock"_s,

            "StartClock"_s                  +         event<Timeout>                                     =           state<FightState>,
            "StartClock"_s                  +         event<Terminate>                                   =           "DisengageRobot"_s,

            //state<FightState>             +         on_entry<_>          / (ACTIONS),
            state<FightState>               +         event<Terminate>                                   =           "DisengageRobot"_s,

            "DisengageRobot"_s              +         event<Reset>                                       =           "Configuration"_s);
    };
};

sml::sm<machine> Core;

#endif