#ifndef SEARCH_SELECTOR_HPP
#define SEARCH_SELECTOR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configuration.hpp"
#include "../../strategies/search_strategies/search_none.hpp"

namespace sml = boost::sml;

struct SearchSelector
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "selector"_s,
            "selector"_s = state<SearchNone>);
    }
};

#endif
