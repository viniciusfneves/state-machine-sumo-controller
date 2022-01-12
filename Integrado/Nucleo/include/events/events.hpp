#pragma once

// Aqui são definidos todos os possíveis eventos que podem ser emitidos para a máquina
enum class Event {
    Start,
    Disengage,
    Arm,
    Timeout,
    EdgeDetected,
    OpponentDetected,
    Controller,
    None
};

struct Start {};

struct Disengage {};

struct Arm {};

struct Timeout {};

struct EdgeDetected {};

struct OpponentDetected {};

struct Controller {};

struct None {};
