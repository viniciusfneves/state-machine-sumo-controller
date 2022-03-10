#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../events/events.hpp"
#include "../../motors/PID_controller.hpp"

namespace sml = boost::sml;

struct StandardChase {
    auto operator()() const {
        auto chaseAction = [] { driveRobot(1, pid.calculateOutput(getErrorFromOPSensors())); };

        using namespace sml;
        return make_transition_table(
            *"entry"_s = "chase"_s,
            "chase"_s  +  event<OpponentDetected>  /  chaseAction);
    }
};
