#ifndef TELEMETRY_TIMEOUT_HPP
#define TELEMETRY_TIMEOUT_HPP

#include <Arduino.h>

bool _interval_active = false; //Indica se Timeout está ativo

int _refreshRate = 42; // Taxa de envio dos dados da telemetria via websocket

unsigned long _pollingTime; //Indica qual o tempo, em milissegundos, que o evento Timeout deve ser disparado

bool isTelemetryActive() { return _interval_active; };

bool readToSend(unsigned long time){
    if(time >= _pollingTime){
        return true;
    }
    return false;
}

//Ativa a função de telemetria do robô e seta o intervalo entre atualizações de dados
void setTelemetryBroadcast(int rate = 0)
{
    if (rate != 0){ _refreshRate = rate; }
    _interval_active = true;
    _pollingTime = millis() + _refreshRate;
}

void updateTelemetry()
{
    _pollingTime = millis() + _refreshRate;
}
#endif