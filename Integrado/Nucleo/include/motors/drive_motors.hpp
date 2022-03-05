#pragma once

// Dependências gerais
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

#ifdef ESP32_ENV
#include <analogWrite.h>  // Adiciona a função analogWrite para compilação com ESP32
#endif

// Função de controles dos pinos de ativação dos drivers para motores brushed
void drvDrive(int pwm, int drvIn1, int drvIn2) {
    if (pwm == 0) {
        // Caso for parada
        digitalWrite(drvIn1, true);
        digitalWrite(drvIn2, true);
    } else if (pwm > 0) {
        // Caso for sentido horário
        analogWrite(drvIn1, pwm);
        digitalWrite(drvIn2, false);
    } else {
        // Caso for sentido anti-horario
        analogWrite(drvIn2, -1 * pwm);
        digitalWrite(drvIn1, false);
    }
}

// Movimenta os motores com os PWM definidos como parâmetro de entrada
// int PWM_left -> PWM que será enviado ao motor esquerdo
// int PWM_right -> PWM que será enviado ao motor direito
void driveMotors(int PWM_left, int PWM_right) {
    PWM_left  = constrain(PWM_left, -255, 255);
    PWM_right = constrain(PWM_right, -255, 255);

#ifdef BRUSHLESS
    analogWrite(pins::motors::left, PWM_left);
    analogWrite(pins::motors::right, PWM_right);
#endif

#ifdef BRUSHED
    drvDrive(PWM_left, pins::motors::leftIN1, pins::motors::leftIN2);
    drvDrive(PWM_right, pins::motors::rightIN1, pins::motors::rightIN2);
#endif

#ifdef ESP32_ENV
    robotData.motorsPower[0] = PWM_left;
    robotData.motorsPower[1] = PWM_right;
#endif
};

// Para toda a locomoção do robô
void stopMotors() {
    driveMotors(0, 0);
};

// Realiza as configurações necessárias para a parte de locomoção do robô
void initMotors() {
#ifdef ESP32_ENV
#ifdef BRUSHLESS
    // Define a resolução de saída dos pinos de PWM do ESP32
    analogWriteResolution(pins::motors::left, 12);
    analogWriteResolution(pins::motors::right, 12);
#endif
#ifdef BRUSHED
    // Define a resolução de saída dos pinos de PWM do ESP32
    analogWriteResolution(pins::motors::leftIN1, 12);
    analogWriteResolution(pins::motors::leftIN2, 12);
    analogWriteResolution(pins::motors::rightIN1, 12);
    analogWriteResolution(pins::motors::rightIN2, 12);
#endif
#endif
#ifdef BRUSHLESS
    pinMode(pins::motors::left, OUTPUT);
    pinMode(pins::motors::right, OUTPUT);
    analogWrite(pins::motors::left, 0);
    analogWrite(pins::motors::right, 0);
#endif
#ifdef BRUSHED
    pinMode(pins::motors::leftIN1, OUTPUT);
    pinMode(pins::motors::leftIN2, OUTPUT);
    pinMode(pins::motors::rightIN1, OUTPUT);
    pinMode(pins::motors::rightIN2, OUTPUT);
    digitalWrite(pins::motors::leftIN1, HIGH);
    digitalWrite(pins::motors::leftIN2, HIGH);
    digitalWrite(pins::motors::rightIN1, HIGH);
    digitalWrite(pins::motors::rightIN2, HIGH);
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
    int PWM_left  = ((2 * linearSpeed + angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius))) * robotConfiguration.maxSpeed;
    int PWM_right = ((2 * linearSpeed - angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius))) * robotConfiguration.maxSpeed;

    // Assegura que a velocidade angular vai ser exercida como pedido, podendo alterar a velocidade linear para isso
    double maxSpeed = (PWM_left > PWM_right) ? PWM_left : PWM_right;
    double minSpeed = (PWM_left < PWM_right) ? PWM_left : PWM_right;

    if (maxSpeed > robotConfiguration.maxSpeed) {
        PWM_left -= maxSpeed - robotConfiguration.maxSpeed;
        PWM_right -= maxSpeed - robotConfiguration.maxSpeed;
    } else if (minSpeed < -robotConfiguration.maxSpeed) {
        PWM_left -= minSpeed + robotConfiguration.maxSpeed;
        PWM_right -= minSpeed + robotConfiguration.maxSpeed;
    }

    // Comanda os motores à rodar com as potências calculadas
    driveMotors(PWM_left, PWM_right);
};

// Movimenta o robô em torno do próprio eixo rotacionando-o em 'degrees' graus, recebidos como parâmetro
// Essa função dispara um evento de Timeout após o movimento de rotação ter sido concluído, portanto
// para usa-lá programe a máquina de estados com esse comportamento em mente
// int degrees -> Graus de rotação
// (enum) Direction  -> Define para qual lado o robô irá virar
void rotateRobot(int degrees) {
    // Limita os parâmetros de entrada aos permitidos pela função
    degrees = constrain(degrees, -359, 359);

    int PWM_left  = robotConfiguration.maxSpeed;
    int PWM_right = robotConfiguration.maxSpeed;

    if (degrees > 0) {
        PWM_right *= -1;
    } else {
        PWM_left *= -1;
    }
    // O tempo até completar a rotação ainda precisa ser verificado com testes e modelado para uma função
    setTimeout(abs(degrees * robotConfiguration.angleBias) / (robotConfiguration.maxSpeed * robotConfiguration.speedBias));
    driveMotors(PWM_left, PWM_right);
};
