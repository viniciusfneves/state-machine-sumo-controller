#ifndef CHASE_SELECTOR_HPP
#define CHASE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../strategies/chase_controllers/standard_chase_controller.hpp"
#include "../../configuration/configuration.hpp"

namespace sml = boost::sml;

struct ChaseSelector
{
    auto operator()() const
    {
        using namespace sml;
        
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s = state<StandardChase>);
    }
};

#endif