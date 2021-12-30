#ifndef PS4_CONTROLLER_HPP
#define PS4_CONTROLLER_HPP

#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#include "dynamic_data/dynamic_data.hpp"

void initController() {
    PS4.begin("00:1a:7d:da:71:03");
    PS4.attachOnConnect([] {
        robotData.controllerStatus = ControllerStatus::connected;
    });
    PS4.attachOnDisconnect([] {
        robotData.controllerStatus = ControllerStatus::disconnected;
    });
}

#endif  // PS4_CONTROLLER_HPP