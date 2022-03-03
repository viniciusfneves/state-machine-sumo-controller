#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../configuration/configurations.hpp"

namespace sml = boost::sml;

struct Arco{
    auto operator()() const {
        using namespace sml;
 
        // Funções
        auto configExit  = [] { setTimeout(250); };
        auto runArc = [] { driveRobot(1, robotConfiguration.velAngularArco); };
        
        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s  + on_entry<_>  / (configExit, runArc));
    }
    };
