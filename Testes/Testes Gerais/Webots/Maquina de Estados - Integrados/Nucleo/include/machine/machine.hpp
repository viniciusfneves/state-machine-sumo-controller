#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "../../lib/boost/sml.hpp"
#include "../events/events.hpp"
#include "../actions/actions.hpp"

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

                "initialMove"_s + on_entry<_> / rotate_right,
                "initialMove"_s + event<Time> / run = "Run"_s );
        }
    };

public:
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"initial"_s = "Configuration"_s,

            "Configuration"_s + on_entry<_> / halt,
            "Configuration"_s + event<Time> = "StartClock"_s,

            "StartClock"_s + event<Time> = state<FightState>,
            //"StartClock"_s  +  event<Terminate>  =  "DisengageRobot"_s,

            state<FightState> + event<Time> = "DisengageRobot"_s,
            "DisengageRobot"_s + event<Time> = "Configuration"_s);
    };
};

sml::sm<machine> Core;

#endif