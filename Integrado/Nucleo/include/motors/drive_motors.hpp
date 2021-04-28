#ifndef DRIVE_MOTORS_HPP
#define DRIVE_MOTORS_HPP

// Dependências gerais
#include <configuration/specifications.hpp>
#include <configuration/configurations.hpp>

#ifdef WEBOTS
#include "../webots/motors.hpp"
#include "../webots/webots_time.hpp"
#endif

#ifdef REAL_ROBOT
#include <pins/pins.hpp>

#ifdef ESP32_ENV
#include <analogWrite.h> // Adiciona a função analogWrite para compilação com ESP32
#include <communications/data/send_data.hpp>
#endif

// Movimenta os motores com os PWM definidos como parâmetro de entrada
// int PWM_left -> PWM que será enviado ao motor esquerdo
// int PWM_right -> PWM que será enviado ao motor direito
void driveMotors(int PWM_left, int PWM_right)
{
    PWM_left = constrain(PWM_left, -255, 255);
    PWM_right = constrain(PWM_right, -255, 255);
    analogWrite(pins::motors::leftMotor, PWM_left);
    analogWrite(pins::motors::rightMotor, PWM_right);

#ifdef ESP32_ENV
    broadcastMotors(PWM_left, PWM_right);
#endif
};

// Para toda a locomoção do robô
void stopMotors()
{
    driveMotors(0, 0);
};

// Realiza as configurações necessárias para a parte de locomoção do robô
void initMotors()
{
#ifdef ESP32_ENV
    // Define a resolução de saída dos pinos de PWM do ESP32
    analogWriteResolution(pins::motors::leftMotor, 12);
    analogWriteResolution(pins::motors::rightMotor, 12);
#endif
    pinMode(pins::motors::leftMotor, OUTPUT);
    pinMode(pins::motors::rightMotor, OUTPUT);
    analogWrite(pins::motors::leftMotor, 0);
    analogWrite(pins::motors::rightMotor, 0);
}

#endif // REAL_ROBOT

// Usado para dizer em qual direção o robô deve se mover
enum class Direction
{
    left,
    right
};

// Movimenta o robô baseado nos parâmetros de entrada de velocidade linear e velocidade angular desejada
// double linearSpeed -> Velocidade linear do robô -> Range [-1,1]
// double angularSpeed -> Velocidade angular do robô -> Range [-1,1]
void driveRobot(double linearSpeed, double angularSpeed)
{
    // Limita os parâmetros de entrada aos permitidos pela função
    // Só funciona se os parametros forem de -1 à 1, caso contrário utilize um MAP para definir as velocidas linear e angular
    linearSpeed = constrain(linearSpeed, -1, 1) * robotSpecifications.maxLinearSpeed;
    angularSpeed = constrain(angularSpeed, -1, 1) * robotSpecifications.maxAngularSpeed;

    // Transforma os parâmetros de velocidade linear e angular em sinal PWM para os motores
    int PWM_left  = ((2 * linearSpeed + angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius))) * robotConfiguration.maxSpeed;
    int PWM_right = ((2 * linearSpeed - angularSpeed * (robotSpecifications.wheelBase)) / (2 * (robotSpecifications.wheelRadius))) * robotConfiguration.maxSpeed;

    //Assegura que a velocidade angular vai ser exercida como pedido, podendo alterar a velocidade linear para isso
    double maxSpeed = (PWM_left > PWM_right) ? PWM_left : PWM_right;
    double minSpeed = (PWM_left < PWM_right) ? PWM_left : PWM_right;

    if (maxSpeed > robotConfiguration.maxSpeed)
    {
        PWM_left -= maxSpeed - robotConfiguration.maxSpeed;
        PWM_right -= maxSpeed - robotConfiguration.maxSpeed;
    }
    else if (minSpeed < -robotConfiguration.maxSpeed)
    {
        PWM_left -= minSpeed + robotConfiguration.maxSpeed;
        PWM_right -= minSpeed + robotConfiguration.maxSpeed;
    }

    // Comanda os motores à rodar com as potências calculadas
    driveMotors(PWM_left, PWM_right);
};

// Movimenta o robô em torno do próprio eixo rotacionando-o em 'degrees' graus, recebidos como parâmetro
// int degrees -> Graus de rotação
// (enum) Direction  -> Define para qual lado o robô irá virar
void rotateRobot(int degrees, Direction direction)
{
    // Limita os parâmetros de entrada aos permitidos pela função
    degrees = constrain(degrees, 1, 359);
    int PWM_left = robotConfiguration.maxSpeed;
    int PWM_right = robotConfiguration.maxSpeed;

    if (direction == Direction::right)
    {
        PWM_right *= -1;
    }
    else
    {
        PWM_left *= -1;
    }
    driveMotors(PWM_left, PWM_right);
    delay(static_cast<int>(degrees * 25 / robotConfiguration.maxSpeed)); // O tempo até completar a rotação ainda precisa ser verificado com testes e modelado para uma função
    stopMotors();
};

#endif //DRIVE_MOTORS_HPP