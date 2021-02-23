#ifndef SEARCH_NONE_HPP
#define SEARCH_NONE_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct SearchNone
{
    auto operator()() const
    {
        using namespace sml;
        auto exit_state = [] { setTimeout(0); };

        return make_transition_table(
            *"entry"_s = "exit"_s,
            "exit"_s + on_entry<_> / exit_state);
    }
};

#endif