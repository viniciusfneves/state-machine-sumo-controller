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

        //auto none        = [](Configuration &config) { return config.initialMove == InitialMove::none; };
        //auto full_frente = [](Configuration &config) { return config.initialMove == InitialMove::full_frente; };
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s + on_entry<_> / [] { Serial.println("Entered InitialMove Selector"); },
            //"selector"_s[none] = sml::state<InitialNone>,
            "selector"_s / [] { Serial.println("SHAZAAAM"); } = sml::state<FullFrente>);
    }
};

#endif
