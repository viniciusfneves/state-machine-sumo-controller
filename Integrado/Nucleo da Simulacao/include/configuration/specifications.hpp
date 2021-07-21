#if !defined(SPECIFICATIONS_HPP)
#define SPECIFICATIONS_HPP

#include <string.h>

// Sumo 3kg //

#ifdef SUMO3KG
struct Specifications
{
    // Define o nome do robo
    String robotName = "Atena";

    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 132;           // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2; // Raio das rodas em milímetros
    const double maxLinearSpeed = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};
#endif

// Minis //

#ifdef MERI
struct Specifications
{
    // Define o nome do robo
    String robotName = "Meri";
    
    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 75.2;           // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2; // Raio das rodas em milímetros
    const double maxLinearSpeed = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};
#endif


#ifdef ET_MINI
struct Specifications
{
    // Define o nome do robô
    String robotName = "ET";

    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 75;           // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2; // Raio das rodas em milímetros
    const double maxLinearSpeed = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};
#endif

#ifdef ZE_PEQUENO
struct Specifications
{
    // Define o nome do robo
    String robotName = "Ze";

    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 75;           // Distância entre as rodas em milímetros. Considerando o centro da roda
    const double wheelRadius = 34 / 2; // Raio das rodas em milímetros
    const double maxLinearSpeed = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};
#endif

Specifications robotSpecifications;

#endif // SPECIFICATIONS_HPP
