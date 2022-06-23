#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../strategies/initial_move_strategies/arco.hpp"
#include "../../strategies/initial_move_strategies/desempate_C.hpp"
#include "../../strategies/initial_move_strategies/full_frente.hpp"
#include "../../strategies/initial_move_strategies/initial_none.hpp"
#include "../../strategies/initial_move_strategies/oleh.hpp"
#include "../../strategies/initial_move_strategies/zig_zag.hpp"

namespace sml = boost::sml;

struct InitialMoveSelector {
    auto operator()() const {
        using namespace sml;
        // Funções
        auto entry = [] { updateRobotState(RobotState::exec_initial); };

        // Guards
        auto none        = [] { return robotConfiguration.initialMove == InitialMove::none; };
        auto full_frente = [] { return robotConfiguration.initialMove == InitialMove::full_frente; };
        auto zig_zag     = [] { return robotConfiguration.initialMove == InitialMove::zig_zag; };
        auto arco        = [] { return robotConfiguration.initialMove == InitialMove::arco; };
        auto oleh        = [] { return robotConfiguration.initialMove == InitialMove::oleh; };
        auto desempate_c = [] { return robotConfiguration.initialMove == InitialMove::desempate_c; };

        return make_transition_table(
            *"entry"_s / entry        = "selector"_s,
            "selector"_s[none]        = state<InitialNone>,
            "selector"_s[full_frente] = state<FullFrente>,
            "selector"_s[zig_zag]     = state<ZigZag>,
            "selector"_s[arco]        = state<Arco>,
            "selector"_s[oleh]        = state<Oleh>,
            "selector"_s[desempate_c] = state<DesempateC>
        );
    }
};

#endif