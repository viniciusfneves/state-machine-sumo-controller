#pragma once

#ifdef WEBOTS
#include "../../webots/webots_time.hpp"
#else
#include <Arduino.h>
#endif

bool _timeoutActive = false;  //Indica se Timeout está ativo

bool isTimeoutActive() { return _timeoutActive; };

unsigned long _timeoutTime;  //Indica qual o tempo, em microsegundos, que o evento Timeout deve ser disparado
//---    ---    ---    ---//

// Retorna true caso já seja hora de emitir o evento Timeout, caso contrário, retorna false
bool timeoutAllowed(unsigned long time) {
    if (time >= _timeoutTime) {
        return true;
    }
    return false;
}

//Ativa a função de Timeout
//Após "time" microsegundos o evento será disparado
void setTimeout(unsigned long time) {
    _timeoutActive = true;
    _timeoutTime = micros() + time * 1000;
}

//Cancela o disparo do evento Timeout, caso haja eventos programados
//Essa função deve vir OBRIGATÓRIAMENTE antes da máquina processar o evento de timeout
void cancelTimeout() {
    _timeoutActive = false;
}