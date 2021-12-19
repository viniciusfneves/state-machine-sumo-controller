#ifndef EVENTS_HPP
#define EVENTS_HPP

// Aqui são definidos todos os possíveis eventos que podem ser emitidos para a máquina
enum class Event {
    Start,
    Terminate,
    Reset,
    Timeout,
    EdgeDetected,
    OpponentDetected,
    SetUpClient,
    BroadcastRobotConfiguration,
    BroadcastTelemetryData,
    Controller,
    None
};

struct Start {};

struct Terminate {};

struct Reset {};

struct Timeout {};

struct EdgeDetected {};

struct OpponentDetected {};

struct SetUpClient {};

struct BroadcastRobotConfiguration {};

struct BroadcastTelemetryData {};

struct Controller {};

struct None {};

#endif