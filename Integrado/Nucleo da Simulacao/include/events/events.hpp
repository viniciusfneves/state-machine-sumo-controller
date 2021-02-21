#ifndef EVENTS_HPP
#define EVENTS_HPP

// Aqui são definidos todos os possíveis eventos que podem
// ser emitidos para que a máquina os processe

struct Terminate {};

struct Timeout {};

struct Start {};

struct BorderDetected {};

struct OpponentDetected {};

struct Reset {};

struct None{};

#endif