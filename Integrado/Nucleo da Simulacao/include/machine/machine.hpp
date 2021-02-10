#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <sml.hpp>
#include <events/events.hpp>
#include <actions/actions.hpp>
#include <Arduino.h>

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
                "initialMove"_s + event<Timeout> = "SearchStrategy"_s);
        }
    };

public:
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            "initial"_s = "Configuration"_s,

            "Configuration"_s + event<Start> / []{Serial.println("Transiting to StartClock State");}= "StartClock"_s,

            "StartClock"_s + on_entry<_> / []{Serial.println("Entered StartClack State");},
            "StartClock"_s + event<Timeout> / []{Serial.println("Transiting to FightState");} = state<FightState>,
            "StartClock"_s + event<Terminate> = "DisengageRobot"_s,

            state<FightState> + on_entry<_> / []{Serial.println("Entered FightState");},
            state<FightState> + event<Terminate> = "DisengageRobot"_s,

            "DisengageRobot"_s + on_entry<_> / []{Serial.println("STOP");},
            "DisengageRobot"_s + event<Reset> = "Configuration"_s);
    };
};

sml::sm<machine> Core;

#endif