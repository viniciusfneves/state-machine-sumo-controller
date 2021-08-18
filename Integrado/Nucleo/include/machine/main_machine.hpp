#ifndef MAIN_MACHINE_HPP
#define MAIN_MACHINE_HPP

#include "../../lib/boost/sml.hpp"
#include "../events/events.hpp"
#include "../machine/fight_machine.hpp"
#include "../motors/drive_motors.hpp"

namespace sml = boost::sml;

// MÁQUINA PRINCIPAL
// Responsável pelas macrotransições entre estados do robô

// Função principal de estruturar as máquinas aninhadas e acioná-las conforme necessário
// Além de garantir transições existentes para o estado "DISENGAGED", servindo como FailSafe 

struct Machine
{
    auto operator()() const
    {
        using namespace sml;
        // Funções
        auto set_startClock = []{ setTimeout(4000); };
        auto disengage = [] { stopMotors(); };

        return make_transition_table(
            *"initial"_s                                                      = "Configuration"_s,

            "Configuration"_s    +  event<Start>                              =   "StartClock"_s,


            "StartClock"_s       +  on_entry<_>         /  set_startClock,
            "StartClock"_s       +  event<Timeout>                            =   state<FightMachine>,
            "StartClock"_s       +  event<Terminate>                          =   "DisengageRobot"_s,

            state<FightMachine>  +  event<Terminate>                          =   "DisengageRobot"_s,

            "DisengageRobot"_s   +  on_entry<_>         / disengage,
            "DisengageRobot"_s   +  event<Reset>                              =   "Configuration"_s);
    }
};


// Definição global da máquina de estados
sml::sm<Machine> Core;

#endif