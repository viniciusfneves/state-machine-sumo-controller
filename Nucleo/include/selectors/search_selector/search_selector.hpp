#ifndef SEARCH_SELECTOR_HPP
#define SEARCH_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../motors/PID_controller.hpp"
#include "../../strategies/search_strategies/radar.hpp"
#include "../../strategies/search_strategies/search_none.hpp"
#include "../../strategies/search_strategies/teco.hpp"

namespace sml = boost::sml;

struct SearchSelector {
    auto operator()() const {
        using namespace sml;
        // Funções
        auto entry = [] { pid.resetPID(); updateRobotState(RobotState::exec_search); };

        // Guards
        auto none  = [] { return robotConfiguration.search == Search::none; };
        auto radar = [] { return robotConfiguration.search == Search::radar; };
        auto teco  = [] { return robotConfiguration.search == Search::teco; };

        return make_transition_table(
            *"entry"_s / entry  = "selector"_s,
            "selector"_s[none]  = state<SearchNone>,
            "selector"_s[radar] = state<Radar>,
            "selector"_s[teco]  = state<Teco>);
    }
};

#endif
