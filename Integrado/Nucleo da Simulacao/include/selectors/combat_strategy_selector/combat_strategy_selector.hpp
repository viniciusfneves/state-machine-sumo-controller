#ifndef COMBAT_STRATEGY_SELECTOR_HPP
#define COMBAT_STRATEGY_SELECTOR_HPP

#include <sml.hpp>
#include <strategies/chase_controllers/standard_chase_controller.hpp>
//#include <configuration/configuration.hpp>
//#include <utilities/timeout_implementation/timeout.hpp>

namespace sml = boost::sml;

struct CombatStrategySelector
{
    auto operator()() const
    {
        //auto none = []() { return true; };

        using namespace sml;
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s = state<StandardChase>);
    }
};

#endif