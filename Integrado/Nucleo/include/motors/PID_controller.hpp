#if !defined(PID_CONTROLLER_HPP)
#define PID_CONTROLLER_HPP

#include "../configuration/configurations.hpp"

double &Kp = robotConfiguration.Kp;
double &Ki = robotConfiguration.Ki;
double &Kd = robotConfiguration.Kd;
double &maxAngularOutput = robotConfiguration.maxAngularSpeedInChase;

double proportional = 0, integral = 0, derivative = 0;
double last_error = 0, output = 0;

double pid(double error)
{
    proportional = Kp / 10 * error;
    integral += Ki * error / 1000;
    derivative = Kd * (error - last_error);

    output = proportional + integral + derivative;

    last_error = error;

    return constrain(output,-maxAngularOutput,maxAngularOutput);
}

void resetPID()
{
    integral = 0;
}

#endif // PID_CONTROLLER_HPP
