#pragma once

#include <utilities/timeout_implementation/timeout.hpp>

#include "../../../lib/boost/sml.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct FullFrente {
    auto operator()() const {
        using namespace sml;
        // Funções
        auto configExit  = [] { setTimeout(robotConfiguration.fullFrenteTimeout); };
        auto runForwards = [] { driveRobot(1, 0); };

        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s  + on_entry<_>  / (configExit, runForwards));
    }
};
