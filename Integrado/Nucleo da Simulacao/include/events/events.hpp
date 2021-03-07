#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <CircularBuffer.h>

// Aqui são definidos todos os possíveis eventos que podem
// ser emitidos para que a máquina os processe
enum class Event
{
    Terminate,
    Timeout,
    SendRobotConfig,
    Start,
    EdgeDetected,
    OpponentDetected,
    Reset,
    None
};

struct Terminate{};

struct Timeout{};

struct SendRobotConfig{};

struct Start{};

struct EdgeDetected{};

struct OpponentDetected{};

struct Reset{};

struct None{};


// Buffer circular
// Utilizado nesse código com lógica FIFO - First In -> First Out
// Mais informações da biblioteca utilizada em: https://github.com/rlogiacco/CircularBuffer?utm_source=platformio&utm_medium=piohome
CircularBuffer<Event, 10> eventQueue;

// Retorna se há eventos para a máquina processar na fila
bool anyEventOnQueue(){
    return !eventQueue.isEmpty();
}

// Retorna o evento que precisa ser processado
Event eventToProcess(){
    return eventQueue.shift();
};

// Adiciona um evento na fila para ser processado
void addEventToQueue(Event event){
    eventQueue.push(event);
};
#endif