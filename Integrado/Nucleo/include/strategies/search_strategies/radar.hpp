#ifndef RADAR_HPP
#define RADAR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../dynamic_data/dynamic_data.hpp"
#include "../../configuration/configurations.hpp"

namespace sml = boost::sml;

struct SearchRadar
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto left  = [] { return getErrorFromOPSensors() <= 0; };
        auto right = [] { return getErrorFromOPSensors() > 0; };

        // Funções
        auto rotate_left = [] { driveRobot(0, -1 * robotConfiguration.radarSpeed); };
        auto rotate_right = [] { driveRobot(0, robotConfiguration.radarSpeed); };

        return make_transition_table(
            *"entry"_s = "switch"_s,

            "switch"_s  [left]   = "rotate_left"_s,
            "switch"_s  [right]  = "rotate_right"_s,

            "rotate_left"_s   + on_entry<_>  / rotate_left,
            "rotate_right"_s  + on_entry<_>  / rotate_right);
    }
};
#endif