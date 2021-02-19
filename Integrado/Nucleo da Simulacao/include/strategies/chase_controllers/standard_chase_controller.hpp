#ifndef CHASE_CONTROLLER_HPP
#define CHASE_CONTROLLER_HPP

#include <sml.hpp>
#include <events/events.hpp>

namespace sml = boost::sml;

struct StandardChase
{
    auto operator()() const
    {
        auto chase_action = [] {};
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "chase"_s,
            "chase"_s + event<OpponentDetected> / chase_action);
    };
};

#endif