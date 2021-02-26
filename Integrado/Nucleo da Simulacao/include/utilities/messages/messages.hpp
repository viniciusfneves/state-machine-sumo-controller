#if !defined(MESSAGES_HPP)
#define MESSAGES_HPP

#ifdef REAL_ROBOT
#include <Arduino.h>
#endif
#ifndef REAL_ROBOT
#include <iostream>
using namespace std;
#endif

void display_message(const char *message)
{
#ifdef REAL_ROBOT
    Serial.println(message);
#endif
#ifndef REAL_ROBOT
    cout << message << endl;
#endif
};

#endif // MESSAGES_HPP
