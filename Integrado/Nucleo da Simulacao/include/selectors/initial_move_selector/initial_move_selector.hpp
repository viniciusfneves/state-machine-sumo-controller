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
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s = sml::state<FullFrente>);
    }
};

#endif
