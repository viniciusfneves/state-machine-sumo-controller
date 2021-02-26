#ifndef FIGHT_MACHINE_HPP
#define FIGHT_MACHINE_HPP

#include "../../lib/boost/sml.hpp"
#include "../selectors/initial_move_selector/initial_move_selector.hpp"
#include "../selectors/search_selector/search_selector.hpp"
#include "../selectors/chase_selector/chase_selector.hpp"
#include "../motors/drive_motors.hpp"

namespace sml = boost::sml;


// MÁQUINA DE LUTA
// Responsável pela transição de estados no momento da luta
struct FightMachine
{
    auto operator()() const
    {
        using namespace sml;

        // Funções
        auto avoidEdge = [] {stop();drive(-120,-120);delay(200);};

        return make_transition_table(
            *"entry"_s                                                                    = state<InitialMoveSelector>,
            state<InitialMoveSelector>       + event<Timeout>                             = state<SearchSelector>,
            state<InitialMoveSelector>       + event<EdgeDetected>     / avoidEdge      = "AvoidEdge"_s,

            "AvoidEdge"_s                                                                 = state<SearchSelector>,

            state<SearchSelector>            + event<OpponentDetected>                    = state<ChaseSelector>,
            
            state<ChaseSelector>             + event<None>                                = state<SearchSelector>);
    }
};
#endif