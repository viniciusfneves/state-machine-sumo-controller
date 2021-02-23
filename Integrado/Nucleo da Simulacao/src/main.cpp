#include <event_handler/event_handler.hpp>
#include <pins/pins.hpp>
#include <Arduino.h>

void setup()
{
// Configurações específicas para o ESP32
#ifdef SUMO3KG
    Serial.begin(115200); // Porta Serial

    // Define a resolução de saída dos pinos de PWM do ESP32
    analogWriteResolution(pins::leftMotor, 12);
    analogWriteResolution(pins::rightMotor, 12);
#endif

#ifdef SUMOMINI
    Serial.begin(9600);
#endif

    pinMode(pins::leftMotor, OUTPUT);
    pinMode(pins::rightMotor, OUTPUT);
}

void loop()
{
    handle_events();
}