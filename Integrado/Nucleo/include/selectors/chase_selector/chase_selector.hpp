#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../strategies/chase_controllers/standard_chase_controller.hpp"

namespace sml = boost::sml;

struct ChaseSelector {
    auto operator()() const {
        using namespace sml;
        //Funções
        auto entry    = [] { changeRobotState(RobotState::exec_chase); };

        // Guards
        auto standard = [] { return robotConfiguration.chase == Chase::standard; };

        return make_transition_table(
            *"entry"_s  / entry     = "selector"_s,
            "selector"_s [standard] = state<StandardChase>);
    }
};
