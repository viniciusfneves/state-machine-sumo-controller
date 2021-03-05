#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration_object.hpp"
#include "../../utilities/messages/messages.hpp"
#include "../../strategies/initial_move_strategies/initial_none.hpp"
#include "../../strategies/initial_move_strategies/full_frente.hpp"
#include "../../strategies/initial_move_strategies/zig_zag.hpp"

namespace sml = boost::sml;

struct InitialMoveSelector
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto none         = [] { return config.initialMove == InitialMove::none; };
        auto full_frente  = [] { return config.initialMove == InitialMove::full_frente; };
        auto zig_zag      = [] { return config.initialMove == InitialMove::zig_zag; };

        return make_transition_table(
            *"entry"_s / [] { displayMessage("Entered Initial Move Selector"); } = "selector"_s,
            "selector"_s  [none]         = state<InitialNone>,
            "selector"_s  [full_frente]  = state<FullFrente>,
            "selector"_s  [zig_zag]      = state<ZigZag>);
    }
};

#endif
