#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../strategies/initial_move_strategies/full_frente.hpp"
#include "../../strategies/initial_move_strategies/initial_none.hpp"
#include "../../strategies/initial_move_strategies/zig_zag.hpp"

namespace sml = boost::sml;

struct InitialMoveSelector {
    auto operator()() const {
        using namespace sml;
        // Funções
        auto entry = [] { changeRobotState(RobotState::exec_initial); };

        // Guards
        auto none        = [] { return robotConfiguration.initialMove == InitialMove::none; };
        auto full_frente = [] { return robotConfiguration.initialMove == InitialMove::full_frente; };
        auto zig_zag     = [] { return robotConfiguration.initialMove == InitialMove::zig_zag; };

        return make_transition_table(
            *"entry"_s / entry        = "selector"_s,
            "selector"_s[none]        = state<InitialNone>,
            "selector"_s[full_frente] = state<FullFrente>,
            "selector"_s[zig_zag]     = state<ZigZag>);
    }
};

#endif
