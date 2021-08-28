#if !defined(SPECIFICATIONS_HPP)
#define SPECIFICATIONS_HPP

#include <string.h>

/* ---> PRECISA ESTAR DEFINIDO INDEPENDENTE DO AMBIENTE <--- */
#define NUMBER_OF_CONTROLLER_CHANNELS 2

struct Specifications
{
    // 3KG //

#ifdef VAL
    // Define o nome do robo
    const char *robotName = "Valeska";
    // Quantidade de sensores de cada categoria (Borda e Oponente)
#define NUMBER_OF_EDGE_SENSORS 2
#define NUMBER_OF_OPPONENT_SENSORS 5
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 132;           // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2; // Raio das rodas em milímetros
#endif

#ifdef ATENA
    // Define o nome do robo
    const char *robotName = "Atena";
    // Quantidade de sensores de cada categoria (Borda e Oponente)
#define NUMBER_OF_EDGE_SENSORS 2
#define NUMBER_OF_OPPONENT_SENSORS 5
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 132;           // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2; // Raio das rodas em milímetros
#endif

#ifdef APOLO
    // Define o nome do robo
    const char *robotName = "Apolo";
    // Quantidade de sensores de cada categoria (Borda e Oponente)
#define NUMBER_OF_EDGE_SENSORS 4
#define NUMBER_OF_OPPONENT_SENSORS 7
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 132;           // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2; // Raio das rodas em milímetros
#endif

    // MINIS //

#ifdef MERI
    // Define o nome do robo
    String robotName = "Meri";
    // Quantidade de sensores de cada categoria (Borda e Oponente)
#define NUMBER_OF_EDGE_SENSORS 2
#define NUMBER_OF_OPPONENT_SENSORS 5
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 75.2;        // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2; // Raio das rodas em milímetros
#endif

#ifdef ET_MINI
    // Define o nome do robô
    const char *robotName = "ET";
    // Quantidade de sensores de cada categoria (Borda e Oponente)
#define NUMBER_OF_EDGE_SENSORS 2
#define NUMBER_OF_OPPONENT_SENSORS 2
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 75;          // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2; // Raio das rodas em milímetros
#endif

#ifdef ZE_PEQUENO
    // Define o nome do robo
    String robotName = "Ze";
    // Quantidade de sensores de cada categoria (Borda e Oponente)
#define NUMBER_OF_EDGE_SENSORS 2
#define NUMBER_OF_OPPONENT_SENSORS 5
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 75;          // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2; // Raio das rodas em milímetros
#endif

    // SIMULAÇÃO //

#ifdef WEBOTS
#define NUMBER_OF_EDGE_SENSORS 2
#define NUMBER_OF_OPPONENT_SENSORS 2
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 132;           // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2; // Raio das rodas em milímetros
#endif

    // GERAL //

    const double maxLinearSpeed = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};

// Objeto de especificações do robô
Specifications robotSpecifications;

#endif // SPECIFICATIONS_HPP
