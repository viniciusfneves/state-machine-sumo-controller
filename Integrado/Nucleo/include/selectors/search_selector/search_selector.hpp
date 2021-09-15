#ifndef SEARCH_SELECTOR_HPP
#define SEARCH_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../motors/PID_controller.hpp"
#include "../../strategies/search_strategies/search_none.hpp"
#include "../../strategies/search_strategies/radar.hpp"
#ifdef ESP32_ENV
#include "../../communications/data/send_data.hpp"
#endif

namespace sml = boost::sml;

struct SearchSelector
{
    auto operator()() const
    {
        using namespace sml;
        //Funções
        auto entry = []
        { 
            resetPID(); 
#ifdef ESP32_ENV
            broadcastRobotState(RobotState::exec_search); 
#endif
        };

        // Guards
        auto none   = [] { return robotConfiguration.search == Search::none; };
        auto radar  = [] { return robotConfiguration.search == Search::radar; };

        return make_transition_table(
            *"entry"_s  / entry  = "selector"_s,
            "selector"_s [none]  = state<SearchNone>,
            "selector"_s [radar] = state<SearchRadar>);
    }
};

#endif
