#ifndef SHORT_RIGHT_ARCH_HPP
#define SHORT_RIGHT_ARCH_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../configuration/configurations.hpp"

namespace sml = boost::sml;

struct ShortRightArch
{
    auto operator()() const
    {
        using namespace sml;
        // Funções
        auto exitState  = [] { setTimeout(250); };
        auto shortRightArch = [] { driveRobot(robotConfiguration.archLinearVelocity,robotConfiguration.shortArchAngularVelocity); };
        
        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s  + on_entry<_>  / (exitState, shortRightArch));
    }
};

#endif