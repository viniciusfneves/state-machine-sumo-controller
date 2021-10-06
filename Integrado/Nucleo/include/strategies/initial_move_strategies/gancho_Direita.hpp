#ifndef GANCHO_DIREITA_HPP
#define GANCHO_DIREITA_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct GanchoDireita
{
    auto operator()() const
    {
        using namespace sml;

        auto arc_to_right      = [] { driveRobot(0.7, 0.3); setTimeout(200); };
        auto look_back          =[] { driveRobot(0,1); setTimeout(50); };

        auto exitState  = [] { setTimeout(0); };

        //Arco curto pela direita
        return make_transition_table(
            *"initial"_s                            / arc_to_right                  = "running"_s,
            "running"_s                             / look_back                        = "ready_to_fight"_s,
            "ready_to_fight"_s    + event<Timeout>     / existState              = "terminate"_s,
    }
};

#endif