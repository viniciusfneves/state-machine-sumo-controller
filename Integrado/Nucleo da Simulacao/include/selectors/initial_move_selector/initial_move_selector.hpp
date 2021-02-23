#ifndef INITIAL_MOVE_SELECTOR_HPP
#define INITIAL_MOVE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration.hpp"
#include "../../strategies/initial_move_strategies/initial_none.hpp"
#include "../../strategies/initial_move_strategies/full_frente.hpp"

namespace sml = boost::sml;

// ISSO NECESSARIAMENTE PRECISA SER UMA CLASSE
// TODOS OS SELETORES DE ESTRATÉGIA PRECISAM SER UMA CLASSE
// Em uma struct os guards apresentam erro
class InitialMoveSelector
{
public:
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s = sml::state<FullFrente>);
    }
};

#endif
