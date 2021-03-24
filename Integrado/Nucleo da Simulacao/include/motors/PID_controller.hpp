#if !defined(PID_CONTROLLER_HPP)
#define PID_CONTROLLER_HPP

#include "../configuration/configurations.hpp"

double& Kp = robotConfiguration.Kp;
double& Ki = robotConfiguration.Ki;
double& Kd = robotConfiguration.Kd;

double pid(double error)
{
    double proportional = 0, integral = 0, derivative = 0;
    double last_error = 0, output = 0;

    proportional    = Kp * error;
    integral        = integral + Ki * error;
    derivative      = Kd * (error - last_error);

    output = proportional + integral + derivative;

    last_error = error;

    return output;
}

#endif // PID_CONTROLLER_HPP
