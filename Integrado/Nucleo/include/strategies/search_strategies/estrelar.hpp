#ifndef ESTRELAR_HPP
#define ESTRELAR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"

namespace sml = boost::sml;

struct Estrelar
{
    auto operator()() const
    {
        using namespace sml;

        //Guards
        auto borda_detectada = [] { return isEdgeDetected() }

        //Funções
        auto full_frente = []{ driveRobot(1,0);};
        auto girar_esquerda = []{ driveRobot(0,-1); setTimeout(100);};
        auto girar_direita = []{ driveRobot(0,1); setTimeout(100);};
        auto exitState  = [] { setTimeout(0); };

        //Arco curto pela direita
        return make_transition_table(
            *"initial"_s                            / full_frente                           = "andando"_s,
            "andando"_s [borda_detectada_direta]           / girar_esquerda                = "initial"_s,
            "andando"_s [borda_detectada_esquerda]           / girar_direita                = "initial"_s,
            
            "andando"_s [robo_detectado]            / exitState                             = "ready_to_fight"_s,
            "ready_to_fight"_s    + event<Timeout>     / exitState                          = "terminate"_s,
    }
};

#endif

//Como retornar qual sensor de borda detectou a borda? Direita ou esquerda?
//Event<Timeout> está certo?
//Parar fazer um "if" é usando colchete depois do evento?
//Como faz para voltar para o estado inicial? Como é feito no radar?
//Se o radar perder o robô adversário, como ele volta para a busca?
//"On_entry" e "Event" no zigzag faz a transição ficar diferente, com parenteses. Como assim?