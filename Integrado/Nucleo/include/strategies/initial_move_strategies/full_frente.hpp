#ifndef FULL_FRENTE_HPP
#define FULL_FRENTE_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct FullFrente {
    auto operator()() const {
        using namespace sml;
        // Funções
        auto configExit  = [] { setTimeout(250); };
        auto runForwards = [] { driveRobot(1, 0); };
        
        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s  + on_entry<_>  / (configExit, runForwards));
    }
};

#endif