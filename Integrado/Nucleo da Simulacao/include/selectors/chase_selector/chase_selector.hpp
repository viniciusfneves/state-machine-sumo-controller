#ifndef CHASE_SELECTOR_HPP
#define CHASE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration_object.hpp"
#include "../../utilities/messages/messages.hpp"
#include "../../strategies/chase_controllers/standard_chase_controller.hpp"

namespace sml = boost::sml;

struct ChaseSelector
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto standard = [] { return config.chase == Chase::standard; };

        return make_transition_table(
            *"entry"_s / [] { displayMessage("Entered Chase Selector"); }  = "selector"_s,
            "selector"_s = state<StandardChase>);
    }
};

#endif