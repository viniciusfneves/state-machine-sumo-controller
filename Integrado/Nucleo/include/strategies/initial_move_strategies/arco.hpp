#pragma once

#include "../../../lib/boost/sml.hpp"
#include "../../configuration/configurations.hpp"
#include "../../events/events.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"

namespace sml = boost::sml;

struct Arco {
    auto operator()() const {
        using namespace sml;

        // Funções
        auto configExit = [] { setTimeout(robotConfiguration.arcTimeout); };
        auto runArc     = [] { driveRobot(1, robotConfiguration.arcAgularSpeed); };
        auto rotaciona  = [] { rotateRobot(robotConfiguration.angle); };

        return make_transition_table(
            *"entry"_s = "rotating"_s,

            // Não é necessário chamar setTimeout em "rotating"_s pois a função
            // rotateRobot emite um evento de Timeout quando o movimento de rotação for concluído
            "rotating"_s / rotaciona = "moving"_s,

            "moving"_s + event<Timeout> / (configExit, runArc) = "exit"_s);
    }
};
