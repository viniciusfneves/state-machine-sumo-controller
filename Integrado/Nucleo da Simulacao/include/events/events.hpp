#ifndef EVENTS_HPP
#define EVENTS_HPP

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
    Controller,
    Reset,
    None
};

struct Terminate{};

struct Timeout{};

struct SendRobotConfig{};

struct Start{};

struct EdgeDetected{};

struct OpponentDetected{};

struct Controller{};

struct Reset{};

struct None{};

#endif