#ifndef RADAR_HPP
#define RADAR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../motors/drive_motors.hpp"

#include <iostream>

namespace sml = boost::sml;

#define tal 100

struct SearchRadar
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto left  = [] { return true; };  // Implementar função para verificar qual o último lado visto pelos sensores de oponentes
        auto right = [] { return false; }; // Implementar função para verificar qual o último lado visto pelos sensores de oponentes

        // Funções MINI
        auto rotate_left = []
        {
            static double tRadar1 = millis();
            driveRobot(
                0,
                -1 + exp(-(millis() - tRadar1) * tal));
        };
        auto rotate_right = []
        {
            static double tRadar2 = millis();
            driveRobot(
                0,
                1 - exp(-(millis() - tRadar2) * tal));
        };


        return make_transition_table(
            *"entry"_s = "switch"_s,

            "switch"_s  [left]   = "rotate_left"_s,
            "switch"_s  [right]  = "rotate_right"_s,

            "rotate_left"_s   + on_entry<_>  / rotate_left,
            "rotate_left"_s   = "switch"_s,
            "rotate_right"_s  + on_entry<_>  / rotate_right,
            "rotate_right"_s  = "switch"_s
        );
    }
};
#endif