#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../events/events.hpp"
#include "../../motors/drive_motors.hpp"
#include <utilities/timeout_implementation/timeout.hpp>

namespace sml = boost::sml;

struct Oleh {
    auto operator()() const {
        using namespace sml;

        // Funções
        auto runForwards = [] { driveRobot(1, 0); setTimeout(300); };
        auto rotate      = [] { rotateRobot(robotConfiguration.angle); };
        auto configExit  = [] { setTimeout(robotConfiguration.shortArcTimeout); };
        auto runArc      = [] { driveRobot(1, robotConfiguration.shortArcAgularSpeed); };

        return make_transition_table(
            *"entry"_s                                              = "runForwards"_s,
            "runForwards"_s                  / runForwards          = "rotating"_s,
            "rotating"_s    + event<Timeout> / rotate               = "arc"_s,
            "arc"_s         + event<Timeout> / (configExit, runArc) = "exit"_s);
    }
};
