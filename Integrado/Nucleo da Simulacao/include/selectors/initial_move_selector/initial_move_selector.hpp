#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration.hpp"
#include "../../strategies/initial_move_strategies/initial_none.hpp"
#include "../../strategies/initial_move_strategies/full_frente.hpp"

namespace sml = boost::sml;

struct InitialMoveSelector
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto none         = [] { return config.initialMove == InitialMove::none; };
        auto full_frente  = [] { return config.initialMove == InitialMove::full_frente; };

        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s  [none]         = state<InitialNone>,
            "selector"_s  [full_frente]  = state<FullFrente>);
    }
};

#endif
