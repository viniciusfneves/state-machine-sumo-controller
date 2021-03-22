#ifndef ZIG_ZAG_HPP
#define ZIG_ZAG_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../event_handler/event_handler.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct ZigZag
{
    auto operator()() const
    {
        using namespace sml;

        auto exit_state = [] { setTimeout(0); };
        auto run_forwards1 = [] { driveMotors(100, 100) ; delay(250); };
        auto spin_left = [] { driveMotors(-70,70); delay(120); };
        auto run_forwards2 = [] { driveMotors(120, 120) ; delay(250); };

        //Zigzag curto pela direita
        return make_transition_table(
            *"entry"_s = "run_forwards1"_s,
            "run_forwards1"_s / run_forwards1 = "spin"_s,
            "spin"_s / spin_left = "run_forwards2"_s,
            "run_forwards2"_s + on_entry<_> / (run_forwards2, exit_state));
    }
};

#endif