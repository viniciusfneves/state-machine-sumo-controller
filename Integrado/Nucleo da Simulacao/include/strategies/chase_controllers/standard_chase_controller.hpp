#ifndef CHASE_CONTROLLER_HPP
#define CHASE_CONTROLLER_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../events/events.hpp"
#include "../../sensors/opponent_sensor/opponent_sensor.hpp"
#include "../../motors/PID_controller.hpp"

namespace sml = boost::sml;

struct StandardChase
{
    auto operator()() const
    {
        auto chase_action = [] { driveRobot(1, pid(getErrorFromOPSensors())); };
        
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "chase"_s,
            "chase"_s  + event<OpponentDetected>  / chase_action);
    }
};

#endif