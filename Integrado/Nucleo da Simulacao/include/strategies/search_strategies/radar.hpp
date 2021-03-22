#ifndef RADAR_HPP
#define RADAR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct SearchRadar
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto left  = [] { return true; };  // Implementar função para verificar qual o último lado visto pelos sensores de oponentes
        auto right = [] { return false; }; // Implementar função para verificar qual o último lado visto pelos sensores de oponentes

        // Funções
        auto rotate_left = [] { driveMotors(-60, 60); };
        auto rotate_right = [] { driveMotors(60, -60); };

        return make_transition_table(
            *"entry"_s                  = "switch"_s,

            "switch"_s  [left]          = "rotate_left"_s,
            "switch"_s  [right]         = "rotate_right"_s,

            "rotate_left"_s  + on_entry<_> / rotate_left,
            "rotate_right"_s + on_entry<_> / rotate_right);
    }
};
#endif