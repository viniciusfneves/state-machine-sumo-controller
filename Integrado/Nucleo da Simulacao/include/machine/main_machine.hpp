#ifndef MAIN_MACHINE_HPP
#define MAIN_MACHINE_HPP

#include "../../lib/boost/sml.hpp"
#include "../events/events.hpp"
#include "../machine/fight_machine.hpp"

namespace sml = boost::sml;

// MÁQUINA PRINCIPAL
// Responsável pelas macro transições entre estados do robô
// Nela exitem os estados de configuração inicial do robô, máquina de luta
// e todas as transições entre elas, incluindo o desligamento do robô após
// o evento de <Terminate>
struct machine
{
    auto operator()() const
    {
        using namespace sml;
        // Funções
        auto set_startClock = []{setTimeout(4000);};

        return make_transition_table(
            *"initial"_s                                                      = "Configuration"_s,

            "Configuration"_s    +  event<Start>                              =   "StartClock"_s,


            "StartClock"_s       +  on_entry<_>         /  set_startClock,
            "StartClock"_s       +  event<Timeout>                            =   state<FightMachine>,
            "StartClock"_s       +  event<Terminate>                          =   "DisengageRobot"_s,

            state<FightMachine>  +  event<Terminate>                          =   "DisengageRobot"_s,

            "DisengageRobot"_s   +  event<Reset>                              =   "Configuration"_s);
    }
};


// Definição global da máquina de estados
sml::sm<machine> Core;

#endif