#ifndef SEARCH_NONE_HPP
#define SEARCH_NONE_HPP

#include <sml.hpp>
#include <event_handler/event_handler.hpp>

namespace sml = boost::sml;

auto exit_state = [] { setTimeoutEvent(); };

struct SearchNone
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "switch_state"_s,
            "switch_state"_s / exit_state = X);
    }
};

#endif