#ifndef EVENTS_HPP
#define EVENTS_HPP

// Aqui são definidos todos os possíveis eventos que podem
// ser emitidos para que a máquina os processe

enum class Event
{
    Terminate,
    Timeout,
    Start,
    EdgeDetected,
    OpponentDetected,
    Reset,
    None
};

struct Terminate{};

struct Timeout{};

struct Start{};

struct EdgeDetected{};

struct OpponentDetected{};

struct Reset{};

struct None{};


Event eventOnQueue = Event::None;

void addEventToQueue(Event event)
{
    eventOnQueue = event;
};

#endif