#if !defined(PID_CONTROLLER_HPP)
#define PID_CONTROLLER_HPP

#define Kp 60
#define Ki 1
#define Kd 0.4

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
