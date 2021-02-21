#ifndef CHASE_SELECTOR_HPP
#define CHASE_SELECTOR_HPP

#include <sml.hpp>
#include <strategies/chase_controllers/standard_chase_controller.hpp>
//#include <configuration/configuration.hpp>
//#include <utilities/timeout_implementation/timeout.hpp>

namespace sml = boost::sml;

// ISSO NECESSARIAMENTE PRECISA SER UMA CLASSE
// TODOS OS SELETORES DE ESTRATÉGIA PRECISAM SER UMA CLASSE
// Em uma struct os guards apresentam erro
class ChaseSelector
{
    auto operator()() const
    {
        auto standard = [](Configuration &config) { return config.chase == Chase::standard; };

        using namespace sml;
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s [standard]    = state<StandardChase>);
    }
};

#endif