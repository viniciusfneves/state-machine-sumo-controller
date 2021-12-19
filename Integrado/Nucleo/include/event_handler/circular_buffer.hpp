#if !defined(CIRCULAR_BUFFER_HPP)
#define CIRCULAR_BUFFER_HPP

#include "../../lib/CircularBuffer/CircularBuffer.h"
#include "../events/events.hpp"
// Buffer circular
// Utilizado nesse código com lógica FIFO ---> |First In -> First Out|
// Mais informações da biblioteca utilizada em: https://github.com/rlogiacco/CircularBuffer?utm_source=platformio&utm_medium=piohome
CircularBuffer<Event, 10> eventQueue;

// Retorna se há eventos para a máquina processar na fila
bool anyEventOnQueue() {
    return !eventQueue.isEmpty();
}

// Retorna o evento que precisa ser processado
Event eventToProcess() {
    return eventQueue.shift();
};

// Adiciona um evento na fila para ser processado
void addEventToQueue(Event event) {
    eventQueue.push(event);
};

bool eventQueueIsFull() {
    return eventQueue.isFull();
}

#endif  // CIRCULAR_BUFFER_HPP