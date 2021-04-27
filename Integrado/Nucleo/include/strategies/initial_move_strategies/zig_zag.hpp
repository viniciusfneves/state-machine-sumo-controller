#ifndef ZIG_ZAG_HPP
#define ZIG_ZAG_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct ZigZag
{
    auto operator()() const
    {
        using namespace sml;

        auto run_1      = [] { driveRobot(1, 0); delay(150); };
        auto rotate     = [] { driveMotors(-127, 127); delay(90); };
        auto run_2      = [] { driveRobot(1, 0); delay(190); };
        auto exitState  = [] { setTimeout(0); };

        //Zigzag curto pela direita
        return make_transition_table(
            *"entry"_s                                                        = "first_run"_s,
            "first_run"_s                      / run_1                        = "rotate"_s,
            "rotate"_s                         / rotate                       = "second_run"_s,
            "second_run"_s    + on_entry<_>    / (run_2, exitState));
    }
};

#endif