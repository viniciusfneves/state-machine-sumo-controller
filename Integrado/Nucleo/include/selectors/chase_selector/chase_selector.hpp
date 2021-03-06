#ifndef CHASE_SELECTOR_HPP
#define CHASE_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../utilities/messages/messages.hpp"
#include "../../strategies/chase_controllers/standard_chase_controller.hpp"

namespace sml = boost::sml;

struct ChaseSelector
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto standard = [] { return robotConfiguration.chase == Chase::standard; };

        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s [standard] = state<StandardChase>);
    }
};

#endif