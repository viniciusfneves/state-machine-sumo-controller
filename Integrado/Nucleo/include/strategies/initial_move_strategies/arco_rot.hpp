#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../configuration/configurations.hpp"

namespace sml = boost::sml;

//arco com rotação
struct ArcoRot{
    auto operator()() const {
        using namespace sml;
 
        // Funções
        auto configExit  = [] { setTimeout(250); };
        auto runArc = [] { driveRobot(1, robotConfiguration.arcAngularSpeed); };
        auto rotaciona = []{rotateRobot( robotConfiguration.angle, robotConfiguration.direction);}
        
        return make_transition_table(
            *"entry"_s = "rotating"_s,
            "rotating"_s                                 /(configExit, rotaciona)
            "moving"_s + on_entry<_>                    / (configExit, runArc));
    }
    };
