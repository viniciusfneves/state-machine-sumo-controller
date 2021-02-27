#ifndef CHASE_SELECTOR_HPP
#define CHASE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration.hpp"
#include "../../utilities/messages/messages.hpp"
#include "../../strategies/chase_controllers/standard_chase_controller.hpp"

namespace sml = boost::sml;

struct ChaseSelector
{
    auto operator()() const
    {
        using namespace sml;
        
        return make_transition_table(
            *"entry"_s / [] { display_message("Entered Chase Selector"); }  = "selector"_s,
            "selector"_s = state<StandardChase>);
    }
};

#endif