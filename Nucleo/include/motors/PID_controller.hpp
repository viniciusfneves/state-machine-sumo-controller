#pragma once

#include "../configuration/configurations.hpp"

class PIDController {
   private:
    double &_kp               = robotConfiguration.Kp;
    double &_ki               = robotConfiguration.Ki;
    double &_kd               = robotConfiguration.Kd;
    double &_maxAngularOutput = robotConfiguration.maxAngularSpeedInChase;
    double  _maxIntegrative   = _maxAngularOutput * 0.5;

    double _proportional = 0, _integral = 0, _derivative = 0;
    double _dt = 0, _last_error = 0, _last_timestamp = 0, _output = 0;

   public:
    double calculateOutput(double error) {
        _dt = micros() - _last_timestamp;

        if (_dt >= 1000 || _dt <= 0) {
            _dt = 1;
        }

        _proportional = _kp * error;
        _integral     = _integral + (_ki * error * _dt / 1000000.);
        _integral     = constrain(_integral, -_maxIntegrative, _maxIntegrative);

        _derivative = _kd * (error - _last_error) / (_dt / 1000000.);

        _output = _proportional + _integral + _derivative;

        _last_error     = error;
        _last_timestamp = micros();

        _output = constrain(_output, -_maxAngularOutput, _maxAngularOutput);

        return _output;
    }

    void resetPID() {
        _integral = 0;
    }
};

PIDController pid;
