#ifndef _MOTORS_
    #define _MOTORS_
    #include <webots/Robot.hpp>
    #include <webots/Motor.hpp>
    
    #define MAX_SPEED 6.28

    using namespace webots;

    Motor *initMotor(Robot *, char *);
    void move(Motor *, double, Motor *, double);

#endif