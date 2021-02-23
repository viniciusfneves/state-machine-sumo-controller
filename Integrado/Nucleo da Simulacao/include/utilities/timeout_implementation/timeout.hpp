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
//Indica se Timeout está ativo
bool timeoutActive = false;
//Indica qual o tempo, em milissegundos, que o evento Timeout deve ser disparado
unsigned long timeoutTime;
//---    ---    ---    ---//

//Ativa a função de Timeout
//Após "time" millisegundos o evento será disparado
void setTimeout(unsigned long time)
{
    timeoutActive = true;
    timeoutTime = millis() + time;
}

//Cancela o disparo do evento Timeout, caso haja eventos programados
void cancelTimeout()
{
    timeoutActive = false;
}

#endif