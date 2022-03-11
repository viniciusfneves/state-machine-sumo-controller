#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../events/events.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct DesempateC {
    auto operator()() const {
        using namespace sml;

        // Funções
        auto configExit  = [] { setTimeout(robotConfiguration.shortArcTimeout); };
        auto runArc      = [] { driveRobot(1, robotConfiguration.shortArcAgularSpeed); };
        auto runForwards = [] { driveRobot(1, 0); setTimeout(600); };

        return make_transition_table(
            *"entry"_s                                              = "first_arc"_s,
            "first_arc"_s                    / (configExit, runArc) = "runForwards"_s,
            "runForwards"_s + event<Timeout> / runForwards          = "second_arc"_s
            "second_arc"_s  + event<Timeout> / (configExit, runArc) = "exit"_s);
    }
};
