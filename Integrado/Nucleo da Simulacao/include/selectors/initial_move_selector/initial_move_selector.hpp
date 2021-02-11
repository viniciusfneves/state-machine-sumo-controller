#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include <sml.hpp>
#include <configuration/configuration.hpp>
#include <strategies/initial_move_strategies/initial_none.hpp>

namespace sml = boost::sml;

struct InitialMoveSelector
{
    auto operator()() const
    {
        auto none = [](Configuration &config) { return config.initialMove == InitialMove::none; };

        using namespace sml;
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s[none] = state<InitialNone>);
    }
};

#endif
