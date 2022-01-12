#pragma once

#include <event_handler/circular_buffer.hpp>
#include <pins/pins.hpp>

namespace startModule {
bool lastState = false;
bool currentState = false;
}  // namespace startModule

void initStartModule() {
    pinMode(pins::startModule, INPUT);
}

void readStartModule() {
    startModule::currentState = digitalRead(pins::startModule);
    if (startModule::lastState != startModule::currentState) {
        if (startModule::currentState == 1)
            addEventToQueue(Event::Start);
        else if (robotData.robotState != RobotState::ready)
            addEventToQueue(Event::Disengage);
    }
    startModule::lastState = startModule::currentState;
}
