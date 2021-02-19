#ifndef TIMEOUT_HPP
#define TIMEOUT_HPP

#include <Arduino.h>
#include <machine/main_machine.hpp>
#include <events/events.hpp>

// VARIAVEIS GLOBAIS
//---    ---    ---    ---//

//Indica se Timeout está ativo
bool timeoutActive = false;
//Indica qual o tempo, em milissegundos, que o evento Timeout deve ser disparado
unsigned long timeoutTime;

//Ativa a função de Timeout
//Após "time" millisegundos o evento será disparado
void setTimeout(unsigned long time)
{
    timeoutActive = true;
    timeoutTime = millis() + time;
};

//Cancela o disparo do evento Timeout
void cancelTimeout()
{
    timeoutActive = false;
};

//Dispara o evento Timeout instantaneamente
void triggerTimeoutEvent()
{
    //Core.process_event(Timeout{});
};

#endif