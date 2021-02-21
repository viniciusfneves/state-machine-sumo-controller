#ifndef MAIN_MACHINE_HPP
#define MAIN_MACHINE_HPP

#include <sml.hpp>
#include <events/events.hpp>
#include <machine/fight_machine.hpp>

namespace sml = boost::sml;

//MAIN MACHINE
struct machine
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"initial"_s = "Configuration"_s,

            "Configuration"_s               +         event<Start>                                       =           "StartClock"_s,

            "StartClock"_s                  +         event<Timeout>                                     =           state<FightMachine>,
            "StartClock"_s                  +         event<Terminate>                                   =           "DisengageRobot"_s,

            state<FightMachine>             +         event<Terminate>                                   =           "DisengageRobot"_s,

            "DisengageRobot"_s              +         event<Reset>                                       =           "Configuration"_s);
    };
};

sml::sm<machine> Core;

#endif