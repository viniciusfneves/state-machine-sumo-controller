#ifndef CHASE_SELECTOR_HPP
#define CHASE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../strategies/chase_controllers/standard_chase_controller.hpp"
#ifdef ESP32_ENV
#include "../../communications/data/send_data.hpp"
#endif

namespace sml = boost::sml;

struct ChaseSelector
{
    auto operator()() const
    {
        using namespace sml;
                //Funções
        auto entry = []
        { 
#ifdef ESP32_ENV
            broadcastRobotState(RobotState::exec_chase); 
#endif
        };

        // Guards
        auto standard = [] { return robotConfiguration.chase == Chase::standard; };

        return make_transition_table(
            *"entry"_s  / entry     = "selector"_s,
            "selector"_s [standard] = state<StandardChase>);
    }
};

#endif