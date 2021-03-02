#ifndef SEARCH_NONE_HPP
#define SEARCH_NONE_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct SearchNone
{
    auto operator()() const
    {
        using namespace sml;
        // Funções
        auto exit_state = [] { setTimeout(0); };
        auto stop_motors = [] { stop(); };

        return make_transition_table(
            *"entry"_s = "exit"_s,
            "exit"_s + on_entry<_> / (stop_motors, exit_state));
    }
};

#endif