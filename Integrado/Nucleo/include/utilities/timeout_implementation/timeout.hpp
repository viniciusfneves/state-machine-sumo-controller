#ifndef TIMEOUT_HPP
#define TIMEOUT_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif
#ifdef WEBOTS
#include "../../webots/webots_time.hpp"
#endif

bool _timeoutActive = false; //Indica se Timeout está ativo

bool isTimeoutActive() { return _timeoutActive; };

unsigned long _timeoutTime; //Indica qual o tempo, em milissegundos, que o evento Timeout deve ser disparado
//---    ---    ---    ---//

// Retorna true caso já seja hora de emitir o evento Timeout, caso contrário, retorna false
bool timeoutAllowed(unsigned long time){
    if(time >= _timeoutTime){
        return true;
    }
    return false;
}

//Ativa a função de Timeout
//Após "time" millisegundos o evento será disparado
void setTimeout(unsigned long time)
{
    _timeoutActive = true;
    _timeoutTime = millis() + time;
}

//Cancela o disparo do evento Timeout, caso haja eventos programados
//Essa função deve vir OBRIGATÓRIAMENTE antes da máquina processar o evento de timeout
void cancelTimeout()
{
    _timeoutActive = false;
}

#endif