#include <Arduino.h>
#include <event_handler/event_handler.hpp>
#include <communications/WiFi/WiFi.hpp>

void setup()
{
// Configurações específicas para o ESP32
#ifdef SUMO3KG
    Serial.begin(115200); // Porta Serial
#endif

#ifdef SUMOMINI
    Serial.begin(9600);
#endif

    initCommunications();
    initMotors();
    initOpponentSensors();
    initEdgeSensors();
}

void loop()
{
    handle_Communications();
    processEvents();
}