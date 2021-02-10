#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <sml.hpp>
#include <events/events.hpp>
#include <actions/actions.hpp>

namespace sml = boost::sml;

struct machine
{
    struct FightState
    {
        auto operator()() const
        {
            using namespace sml;
            return make_transition_table(
                *"initial"_s = "initialMove"_s, 
                "initialMove"_s        +         event<Timeout>                                      =          "SearchStrategy"_s);
        }
    };

public:
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"initial"_s = "Configuration"_s,

            "Configuration"_s           +         event<Start>                                       =           "StartClock"_s,

            "StartClock"_s              +         event<Timeout>                                     =           state<FightState>,
            "StartClock"_s              +         event<Terminate>                                   =           "DisengageRobot"_s,

            state<FightState>           +         on_entry<_>           /           run,
            state<FightState>           +         event<Terminate>                                   =           "DisengageRobot"_s,

            "DisengageRobot"_s          +         event<Reset>                                       =           "Configuration"_s);
    };
};

sml::sm<machine> Core;

#endif