#if !defined(MESSAGES_HPP)
#define MESSAGES_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif
#ifdef WEBOTS
#include <iostream>
using namespace std;
#endif

void displayMessage(const char *message)
{
#ifdef REAL_ROBOT
    Serial.println(message);
#endif
#ifdef WEBOTS
    cout << message << endl;
#endif
};

#endif // MESSAGES_HPP
