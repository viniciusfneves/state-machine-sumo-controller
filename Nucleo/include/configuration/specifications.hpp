#pragma once

#include <string.h>

struct Specifications {
    // 3KG //

#ifdef VAL
    // Define o nome do robo
    const char *robotName = "Valeska";
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 132;       // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2;  // Raio das rodas em milímetros
#endif

#ifdef ATENA
    // Define o nome do robo
    const char *robotName = "Atena";
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 132;       // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2;  // Raio das rodas em milímetros
#endif

#ifdef APOLO
    // Define o nome do robo
    const char *robotName = "Apolo";
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 132;       // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2;  // Raio das rodas em milímetros
#endif

    // MINIS //

#ifdef MERI
    // Define o nome do robo
    const char *robotName = "Meri";
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 75.2;    // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2;  // Raio das rodas em milímetros
#endif

#ifdef ET_MINI
    // Define o nome do robô
    const char *robotName = "ET";
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 75;      // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2;  // Raio das rodas em milímetros
#endif

#ifdef ZE_PEQUENO
    // Define o nome do robo
    const char *robotName = "Ze";
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 75;      // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2;  // Raio das rodas em milímetros
#endif

    // SIMULAÇÃO //

#ifdef WEBOTS
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int    wheelBase   = 132;       // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2;  // Raio das rodas em milímetros
#endif

    // GERAL //

    const double maxLinearSpeed  = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};

// Objeto de especificações do robô
Specifications robotSpecifications;
