#ifndef SEARCH_NONE_HPP
#define SEARCH_NONE_HPP

#include <sml.hpp>
#include <event_handler/event_handler.hpp>
#include <utilities/timeout_implementation/timeout.hpp>

namespace sml = boost::sml;

struct SearchNone
{
    auto operator()() const
    {
        auto exit_state = [] { triggerTimeoutEvent(); };
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "switch_state"_s,
            "switch_state"_s + on_entry<_> / exit_state);
    }
};

#endif