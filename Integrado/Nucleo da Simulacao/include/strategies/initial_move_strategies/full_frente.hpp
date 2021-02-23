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
        using namespace sml;
        // Funções
        auto config_exit = [] { setTimeout(1000); };
        auto run_forwards = [] { drive(255, 255); };
        
        return make_transition_table(
            *"entry"_s = "moving"_s,
            "moving"_s + on_entry<_> / (config_exit, run_forwards));
    }
};

#endif