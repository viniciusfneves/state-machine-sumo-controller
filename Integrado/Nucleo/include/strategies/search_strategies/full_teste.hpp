#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../events/events.hpp"
#include "../../motors/PID_controller.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct Teco {
    auto operator()() const {
        using namespace sml;

        auto teco = [] { driveRobot(1, 0); setTimeout(100); };
        auto tecoPara = [] { stopMotors(); setTimeout(1000);};
        
    

        // Funções

        return make_transition_table(
            *"entry"_s                                                = "first_run"_s,
            "first_run"_s                          / teco             = "rotate"_s,
            "rotate"_s       + event<Timeout>      / tecoPara);
    }
};
