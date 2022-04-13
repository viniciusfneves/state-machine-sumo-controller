#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../events/events.hpp"
#include "../../motors/drive_motors.hpp"
#include <utilities/timeout_implementation/timeout.hpp>

namespace sml = boost::sml;

struct DesempateC {
    auto operator()() const {
        using namespace sml;

        // Funções
        auto configExit  = [] { setTimeout(robotConfiguration.arcTimeout); };
        auto runArc      = [] { driveRobot(1, robotConfiguration.arcAgularSpeed); };
        auto runForwards = [] { driveRobot(1, 0); setTimeout(600); };

        return make_transition_table(
            *"entry"_s                                              = "firstArc"_s,
            "firstArc"_s                     / (configExit, runArc) = "runForwards"_s,
            "runForwards"_s + event<Timeout> / runForwards          = "secondArc"_s,
            "secondArc"_s   + event<Timeout> / (configExit, runArc) = "exit"_s
        );
    }
};
