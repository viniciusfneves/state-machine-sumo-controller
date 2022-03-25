#pragma once

// Dependências gerais
#ifdef BRUSHLESS
#include <ESP32Servo.h>
Servo leftMotor;
Servo rightMotor;
#else
#include "../../lib/ESP32 AnalogWrite/src/analogWrite.h"
#endif

#include <configuration/configurations.hpp>
#include <configuration/specifications.hpp>
#include <dynamic_data/robot_data.hpp>
#include <utilities/timeout_implementation/timeout.hpp>

#ifdef WEBOTS
#include "../webots/motors.hpp"
#include "../webots/webots_time.hpp"
#else
#include <pins/pins.hpp>
#endif

// Função de controles dos pinos de ativação dos drivers para motores brushed
void brushedDrive(int pwm, int in1, int in2) {
    if (pwm == 0) {
        // Caso for parada
        analogWrite(in1, 255);
        analogWrite(in2, 255);
    } else if (pwm > 0) {
        // Caso for sentido horário
        analogWrite(in1, pwm);
        analogWrite(in2, 0);
    } else {
        // Caso for sentido anti-horario
        pwm = abs(pwm);
        analogWrite(in1, 0);
        analogWrite(in2, pwm);
    }
}

// Movimenta os motores com os PWM definidos como parâmetro de entrada
// int leftPWM -> PWM que será enviado ao motor esquerdo
// int rightPWM -> PWM que será enviado ao motor direito
void driveMotors(int leftPWM, int rightPWM) {
    leftPWM  = constrain(leftPWM, -255, 255);
    rightPWM = constrain(rightPWM, -255, 255);

#ifdef BRUSHLESS
    int leftESC  = map(leftPWM, -255, 255, 0, 180);
    int rightESC = map(rightPWM, -255, 255, 0, 180);
    leftMotor.write(leftESC);
    rightMotor.write(rightESC);
#endif

#ifdef BRUSHED
    brushedDrive(leftPWM, pins::motors::leftIN1, pins::motors::leftIN2);
    brushedDrive(rightPWM, pins::motors::rightIN1, pins::motors::rightIN2);
#endif

    robotData.motorsPower[0] = leftPWM;
    robotData.motorsPower[1] = rightPWM;
};

// Para toda a locomoção do robô
void stopMotors() {
    driveMotors(0, 0);
};

// Realiza as configurações necessárias para a parte de locomoção do robô
void initMotors() {
#ifdef BRUSHLESS
    // Define a resolução de saída dos pinos de PWM do ESP32
    leftMotor.attach(pins::motors::left);
    rightMotor.attach(pins::motors::right);
    leftMotor.write(0);
    rightMotor.write(0);
#endif
#ifdef BRUSHED
    pinMode(pins::motors::leftIN1, OUTPUT);
    pinMode(pins::motors::leftIN2, OUTPUT);
    pinMode(pins::motors::rightIN1, OUTPUT);
    pinMode(pins::motors::rightIN2, OUTPUT);
    stopMotors();
#endif
}

// Movimenta o robô baseado nos parâmetros de entrada de velocidade linear e velocidade angular desejada
// double linearSpeed -> Velocidade linear do robô -> Range [-1,1]
// double angularSpeed -> Velocidade angular do robô -> Range [-1,1]
void driveRobot(double linearSpeed, double angularSpeed) {
    // Limita os parâmetros de entrada aos permitidos pela função
    // Só funciona se os parametros forem de -1 à 1, caso contrário utilize um MAP para definir as velocidas linear e angular
    linearSpeed  = constrain(linearSpeed, -1, 1) * robotSpecifications.maxLinearSpeed;
    angularSpeed = constrain(angularSpeed, -1, 1) * robotSpecifications.maxAngularSpeed;

    // Transforma os parâmetros de velocidade linear e angular em sinal PWM para os motores
    int leftPWM  = ((2 * linearSpeed + angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius))) * robotConfiguration.maxSpeed;
    int rightPWM = ((2 * linearSpeed - angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius))) * robotConfiguration.maxSpeed;

    // Assegura que a velocidade angular vai ser exercida como pedido, podendo alterar a velocidade linear para isso
    double maxSpeed = (leftPWM > rightPWM) ? leftPWM : rightPWM;
    double minSpeed = (leftPWM < rightPWM) ? leftPWM : rightPWM;

    if (maxSpeed > robotConfiguration.maxSpeed) {
        leftPWM -= maxSpeed - robotConfiguration.maxSpeed;
        rightPWM -= maxSpeed - robotConfiguration.maxSpeed;
    } else if (minSpeed < -robotConfiguration.maxSpeed) {
        leftPWM -= minSpeed + robotConfiguration.maxSpeed;
        rightPWM -= minSpeed + robotConfiguration.maxSpeed;
    }

    // Comanda os motores à rodar com as potências calculadas
    driveMotors(leftPWM, rightPWM);
};

// Movimenta o robô em torno do próprio eixo rotacionando-o em 'degrees' graus, recebidos como parâmetro
// Essa função dispara um evento de Timeout após o movimento de rotação ter sido concluído, portanto
// para usa-lá programe a máquina de estados com esse comportamento em mente
// int degrees -> Graus de rotação
// (enum) Direction  -> Define para qual lado o robô irá virar
void rotateRobot(int degrees) {
    // Limita os parâmetros de entrada aos permitidos pela função
    degrees = constrain(degrees, -359, 359);

    int leftPWM  = robotConfiguration.maxSpeed;
    int rightPWM = robotConfiguration.maxSpeed;

    if (degrees > 0) {
        rightPWM *= -1;
    } else {
        leftPWM *= -1;
    }
    // O tempo até completar a rotação ainda precisa ser verificado com testes e modelado para uma função
    setTimeout(abs(degrees * robotConfiguration.angleBias) / (robotConfiguration.maxSpeed * robotConfiguration.speedBias));
    driveMotors(leftPWM, rightPWM);
};
