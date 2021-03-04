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
        auto chase_action = [] {drive(100 + error*5, 100-error*5);};
        
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "chase"_s,
            "chase"_s + event<OpponentDetected> / chase_action);
    }
};

#endif