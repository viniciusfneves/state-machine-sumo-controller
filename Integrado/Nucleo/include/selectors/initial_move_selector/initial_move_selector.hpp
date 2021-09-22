#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../strategies/initial_move_strategies/initial_none.hpp"
#include "../../strategies/initial_move_strategies/full_frente.hpp"
#include "../../strategies/initial_move_strategies/zig_zag.hpp"
#include "../../strategies/initial_move_strategies/delayed_radar.hpp"
#ifdef ESP32_ENV
#include "../../communications/data/send_data.hpp"
#endif

namespace sml = boost::sml;

struct InitialMoveSelector
{
    auto operator()() const
    {
        using namespace sml;
        //Funções
        auto entry        = [] { changeRobotState(RobotState::exec_initial); };

        // Guards
        auto none          = [] { return robotConfiguration.initialMove == InitialMove::none; };
        auto full_frente   = [] { return robotConfiguration.initialMove == InitialMove::full_frente; };
        auto zig_zag       = [] { return robotConfiguration.initialMove == InitialMove::zig_zag; };
        auto delayed_radar = [] { return robotConfiguration.initialMove == InitialMove::delayed_radar; };

        return make_transition_table(
            *"entry"_s  /  entry          = "selector"_s,
            "selector"_s  [none]          = state<InitialNone>,
            "selector"_s  [full_frente]   = state<FullFrente>,
            "selector"_s  [zig_zag]       = state<ZigZag>,
            "selector"_s  [delayed_radar] = state<DelayedRadar>);
    }
};

#endif
