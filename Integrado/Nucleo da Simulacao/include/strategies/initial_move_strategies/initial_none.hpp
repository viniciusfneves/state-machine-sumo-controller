#ifndef INITIAL_NONE_HPP
#define INITIAL_NONE_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../event_handler/event_handler.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct InitialNone
{
    auto operator()() const
    {
        using namespace sml;
        // Funções
        auto exit_state = [] { setTimeout(0); };
        
        return make_transition_table(
            *"entry"_s = "switch_state"_s,
            "switch_state"_s + on_entry<_> / exit_state);
    }
};

#endif
