#include <event_handler/event_handler.hpp>
#include <pins/pins.hpp>
#include <Arduino.h>


void setup() {
    Serial.begin(9600);
    pinMode(pins::leftMotor, OUTPUT);
    pinMode(pins::rightMotor, OUTPUT);
}

void loop() {
    handle_events();
}