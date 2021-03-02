#ifndef INITIAL_NONE_HPP
#define INITIAL_NONE_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../event_handler/event_handler.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct InitialNone
{
    auto operator()() const
    {
        using namespace sml;
        // Funções
        auto exit_state = [] { setTimeout(0); };
        auto stop_motors = [] { stop(); };

        return make_transition_table(
            *"entry"_s = "switch_state"_s,
            "switch_state"_s + on_entry<_> / (stop_motors, exit_state));
    }
};

#endif
