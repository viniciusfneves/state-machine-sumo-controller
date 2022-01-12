#pragma once

#include "../../lib/boost/sml.hpp"
#include "../events/events.hpp"
#include "../machine/fight_machine.hpp"
#include "../motors/drive_motors.hpp"
#include "../configuration/configurations.hpp"

namespace sml = boost::sml;

// MÁQUINA PRINCIPAL
// Responsável pelas macrotransições entre estados do robô

// Função principal de estruturar as máquinas aninhadas e acioná-las conforme necessário
// Além de garantir transições existentes para o estado "DisengageRobot", servindo como failsafe 

struct Machine
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto mode_auto = []{ return robotConfiguration.mode == Mode::Auto; };
        auto mode_rc   = []{ return robotConfiguration.mode == Mode::RC; };

        // Funções
        auto armRobot        = [] { changeRobotState(RobotState::ready); };
        auto setStartClock   = [] { setTimeout(robotConfiguration.startTime); changeRobotState(RobotState::starting); };
        auto disengageRobot  = [] { stopMotors(); changeRobotState(RobotState::stopped); };

        return make_transition_table(
            *"entry"_s                                                        =  "disengaged"_s,

            "ready_to_fight"_s   +  on_entry<_>         /  armRobot,
            "ready_to_fight"_s   +  event<Start>  [mode_auto]                 =  "start_clock"_s,
            "ready_to_fight"_s   +  event<Start>  [mode_rc]                   =  state<FightMachine>,
            "ready_to_fight"_s   +  event<Disengage>                          =  "disengaged"_s,


            "start_clock"_s      +  on_entry<_>         /  setStartClock,
            "start_clock"_s      +  event<Timeout>                            =  state<FightMachine>,
            "start_clock"_s      +  event<Disengage>                          =  "disengaged"_s,


            state<FightMachine>  +  event<Disengage>                          =  "disengaged"_s,


            "disengaged"_s       +  on_entry<_>         /  disengageRobot,
            "disengaged"_s       +  event<Arm>                                =  "ready_to_fight"_s);
    }
};


// Definição global da máquina de estados
sml::sm<Machine> Core;
