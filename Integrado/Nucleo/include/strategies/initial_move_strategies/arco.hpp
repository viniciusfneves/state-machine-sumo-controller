#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct Arco {
    auto operator()() const {
        using namespace sml;

        // Funções
        auto configExit = [] { setTimeout(1000); };
        auto runArc     = [] { driveRobot(1, robotConfiguration.velAngularArco); };

        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s + on_entry<_> / (configExit, runArc));
    }
};
