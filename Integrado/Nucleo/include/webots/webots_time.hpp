#ifndef WEBOTS_TIME_HPP
#define WEBOTS_TIME_HPP
#include <webots/Robot.hpp>

using namespace webots;

Robot *robot;

void initTime(Robot *robot) {
    robot = robot;
}

unsigned long millis() {
    return (unsigned long)(robot->getTime() * 1000);
}

void delay(unsigned long time) {
    unsigned long now = robot->getTime() * 1000;
    while (millis() < now + time) {
        ;
    }
}

#endif