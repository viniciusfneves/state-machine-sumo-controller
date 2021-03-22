#ifndef CHASE_CONTROLLER_HPP
#define CHASE_CONTROLLER_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../events/events.hpp"
#include "../../sensors/opponent_sensor/opponent_sensor.hpp"

namespace sml = boost::sml;

struct StandardChase
{
    auto operator()() const
    {
        auto chase_action = [] { driveMotors(100 + detectionError*25, 100-detectionError*25); };
        
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "chase"_s,
            "chase"_s + event<OpponentDetected> / chase_action);
    }
};

#endif