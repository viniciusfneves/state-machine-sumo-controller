#pragma once

#include "../../../lib/boost/sml.hpp"
#include <utilities/timeout_implementation/timeout.hpp>
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct ZigZag {
    auto operator()() const {
        using namespace sml;

        auto run_1      = [] { driveRobot(1, 0); setTimeout(400); };
        auto rotate     = [] { driveRobot(0, -0.4); setTimeout(200); };
        auto run_2      = [] { driveRobot(1, 0); setTimeout(320); };
        auto exitState  = [] { setTimeout(0); };

        //Zigzag curto pela direita
        return make_transition_table(
            *"entry"_s                                                = "first_run"_s,
            "first_run"_s                          / run_1            = "rotate"_s,
            "rotate"_s       + event<Timeout>      / rotate           = "second_run"_s,
            "second_run"_s   + event<Timeout>      / run_2            = "final_state"_s,
            "final_state"_s  + event<Timeout>      / exitState        = "exit_state"_s);
    }
};
