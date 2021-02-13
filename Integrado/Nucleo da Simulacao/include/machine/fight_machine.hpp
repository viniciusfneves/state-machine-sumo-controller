#ifndef FIGHT_MACHINE_HPP
#define FIGHT_MACHINE_HPP

#include <sml.hpp>
#include <selectors/initial_move_selector/initial_move_selector.hpp>
#include <selectors/search_selector/search_selector.hpp>

namespace sml = boost::sml;

struct FightMachine
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"entry"_s                                                                   = state<InitialMoveSelector>,
            state<InitialMoveSelector>              + event<Timeout>                     = state<SearchSelector>);
    }
};
#endif