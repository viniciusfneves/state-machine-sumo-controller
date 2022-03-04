#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../events/events.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

// arco com rotação
struct ArcoRot {
    auto operator()() const {
        using namespace sml;

        // Funções
        auto configExit = [] { setTimeout(1000); };
        auto runArc     = [] { driveRobot(1, robotConfiguration.velAngularArco); };
        auto rotaciona  = [] { rotateRobot(robotConfiguration.angle, robotConfiguration.direction); };

        return make_transition_table(
            *"entry"_s                                                =  "rotating"_s,
            "rotating"_s                  /  (configExit, rotaciona)  =  "moving"_s,
            "moving"_s  + event<Timeout>  /  (configExit, runArc)     =  "exit"_s);
    }
};
