#ifndef START_MODULE_HPP
#define START_MODULE_HPP

#include <dynamic_data/dynamic_data.hpp>
#include <event_handler/circular_buffer.hpp>
#include <pins/pins.hpp>

void initStartModule() {
    pinMode(pins::startModule, INPUT);
}

void readStartModule() {
    robotData.currentState = digitalRead(pins::startModule);
    if (robotData.lastState != robotData.currentState) {
        if (robotData.currentState == 1)
            addEventToQueue(Event::Start);
        else if (robotData.robotState != RobotState::ready)
            addEventToQueue(Event::Disengage);
    }
    robotData.lastState = robotData.currentState;
}

#endif  // START_MODULE_HPP