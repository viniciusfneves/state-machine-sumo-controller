#ifndef EVENTS_HPP
#define EVENTS_HPP

// Aqui são definidos todos os possíveis eventos que podem
// ser emitidos para que a máquina os processe

enum class Events
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

#endif