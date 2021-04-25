#if !defined(MESSAGES_HPP)
#define MESSAGES_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif
#ifdef WEBOTS
#include <iostream>
using namespace std;
#endif

template <class T>
void displayMessage(T message)
{
#ifdef REAL_ROBOT
    Serial.println(message);
#endif // REAL_ROBOT

#ifdef WEBOTS
    cout << message << endl;
#endif // WEBOTS
};

#endif // MESSAGES_HPP
