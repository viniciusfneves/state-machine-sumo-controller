#ifndef FULL_FRENTE_HPP
#define FULL_FRENTE_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../event_handler/event_handler.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct FullFrente
{
    auto operator()() const
    {
        auto run_forwards = [] {};
        using namespace sml;
        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s + on_entry<_> / (run_forwards, [] { setTimeout(750); }));
    }
};

#endif