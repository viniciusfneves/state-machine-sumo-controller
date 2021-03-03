#ifndef SEARCH_SELECTOR_HPP
#define SEARCH_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration.hpp"
#include "../../utilities/messages/messages.hpp"
#include "../../strategies/search_strategies/search_none.hpp"
#include "../../strategies/search_strategies/radar.hpp"

namespace sml = boost::sml;

struct SearchSelector
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto none        = [] { return config.search == Search::none; };
        auto radar       = [] { return config.search == Search::radar; };

        return make_transition_table(
            *"entry"_s  / [] { displayMessage("Entered Search Selector"); } = "selector"_s,
            "selector"_s [none]  = state<SearchNone>,
            "selector"_s [radar] = state<SearchRadar>);
    }
};

#endif
