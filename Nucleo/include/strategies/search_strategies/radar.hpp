#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../dynamic_data/robot_data.hpp"
#include "../../configuration/configurations.hpp"

namespace sml = boost::sml;

struct Radar {
    auto operator()() const {
        using namespace sml;
        // Guards
        auto left  = [] { return getErrorFromOPSensors() <= 0; };
        auto right = [] { return getErrorFromOPSensors() > 0; };

        // Funções
        auto rotateLeft  = [] { driveRobot(0, -robotConfiguration.radarSpeed); };
        auto rotateRight = [] { driveRobot(0, robotConfiguration.radarSpeed); };

        return make_transition_table(
            *"entry"_s = "switch"_s,

            "switch"_s  [left]   / rotateLeft   = "rotate_left"_s,
            "switch"_s  [right]  / rotateRight  = "rotate_right"_s);
    }
};