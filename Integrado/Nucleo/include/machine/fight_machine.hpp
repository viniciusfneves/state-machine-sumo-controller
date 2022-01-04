#ifndef FIGHT_MACHINE_HPP
#define FIGHT_MACHINE_HPP

#include "../../lib/boost/sml.hpp"
#include "../configuration/configurations.hpp"
#include "../selectors/initial_move_selector/initial_move_selector.hpp"
#include "../selectors/search_selector/search_selector.hpp"
#include "../selectors/chase_selector/chase_selector.hpp"
#include "../motors/drive_motors.hpp"

namespace sml = boost::sml;

// MÁQUINA DE LUTA
// Responsável pela tabela de transições dos estados Auto e RC e sobre a seleção da máquina de luta de acordo com o modo configurado
class FightMachine
{
    // Máquina de combate para o modo Auto
    struct Auto
    {
        auto operator()() const
        {
            using namespace sml;

            // Funções
            auto avoidEdge = [] { stopMotors(); driveRobot(-0.7,0); setTimeout(400); };

            return make_transition_table(
                *"entry"_s = state<InitialMoveSelector>,
                
                state<InitialMoveSelector>  + event<Timeout>                            =  state<SearchSelector>,
                state<InitialMoveSelector>  + event<EdgeDetected>                       =  "avoid_edge"_s,

                "avoid_edge"_s              + on_entry<_>               /  avoidEdge,
                "avoid_edge"_s              + event<Timeout>                            =  state<SearchSelector>,

                state<SearchSelector>       + event<OpponentDetected>                   =  state<ChaseSelector>,

                state<ChaseSelector>        + event<None>                               =  state<SearchSelector>);
        }
    };

    // Máquina de combate para o modo RC
    struct RC
    {
        auto operator()() const
        {
            using namespace sml;

            // Funções
            auto executeCommand = [] { driveRobot(robotData.controllerInputs[Input::linearSpeed], robotData.controllerInputs[Input::angularSpeed]); };

            return make_transition_table(
                *"entry"_s = "commands"_s,
                "commands"_s  +  event<Controller>  /  executeCommand);
        }
    };

public:
    auto operator()() const
    {
        using namespace sml;

        // Guards
        auto auto_mode = [] { return robotConfiguration.mode == Mode::Auto; };
        auto rc_mode = [] { return robotConfiguration.mode == Mode::RC; };

        return make_transition_table(
            *"entry"_s                  =  "selector"_s,
            "selector"_s [auto_mode]    =  state<Auto>,
            "selector"_s [rc_mode]      =  state<RC>);
    }
};
#endif