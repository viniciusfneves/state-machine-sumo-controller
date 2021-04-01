#if !defined(SPECIFICATIONS_HPP)
#define SPECIFICATIONS_HPP

#include <string.h>

struct Specifications
{
#ifdef REAL_ROBOT
    // Define o nome do robõ
    String robotName = "Atena";
#endif

    // Especificações mecânicas do robô necessárias para alguns algoritmos do código
    const int wheelBase = 132;           // Distância entre as rodas em milímetros
    const double wheelRadius = 72.5 / 2; // Raio das rodas em milímetros
    const double maxLinearSpeed = wheelRadius;
    const double maxAngularSpeed = 2 * wheelRadius / wheelBase;
};

Specifications robotSpecifications;

#endif // SPECIFICATIONS_HPP
