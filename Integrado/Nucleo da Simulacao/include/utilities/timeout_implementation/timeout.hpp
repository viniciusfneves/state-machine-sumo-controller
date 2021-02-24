#ifndef TIMEOUT_HPP
#define TIMEOUT_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif
#ifndef REAL_ROBOT
#include "../../webots/webots_time.hpp"
#endif

// VARIAVEIS GLOBAIS
//---    ---    ---    ---//
bool timeoutActive = false;  //Indica se Timeout está ativo

unsigned long timeoutTime;   //Indica qual o tempo, em milissegundos, que o evento Timeout deve ser disparado
//---    ---    ---    ---//

//Ativa a função de Timeout
//Após "time" millisegundos o evento será disparado
void setTimeout(unsigned long time)
{
    timeoutActive = true;
    timeoutTime = millis() + time;
}

//Cancela o disparo do evento Timeout, caso haja eventos programados
//Essa função deve vir OBRIGATÓRIAMENTE antes da máquina processar o evento de timeout
void cancelTimeout()
{
    timeoutActive = false;
}

#endif