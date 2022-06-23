#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../events/events.hpp"
#include "../../motors/PID_controller.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct Teco {
    auto operator()() const {
        using namespace sml;

        auto start    = [] { setTimeout(0); };
        auto teco     = [] { driveRobot(1, 0); setTimeout(300); };
        auto tecoPara = [] { stopMotors(); setTimeout(1000); };

        // Funções

        return make_transition_table(
            *"entry"_s                            /  start     = "teco"_s,
            "teco"_s         +  event<Timeout>    /  teco      = "teco_parado"_s,
            "teco_parado"_s  +  event<Timeout>    /  tecoPara  = "teco"_s);
    }
};
