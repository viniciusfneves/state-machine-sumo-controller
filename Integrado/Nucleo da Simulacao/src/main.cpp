#include <Arduino.h>
#include <SPIFFS.h>
#include <event_handler/event_handler.hpp>
#include <communications/WiFi/WirelessCom_handler.hpp>

void setup()
{
// Configurações específicas para o ESP32
#ifdef SUMO3KG
    Serial.begin(115200); // Porta Serial

    SPIFFS.begin(); // Inicia o File System do ESP32

    initCommunications();
#endif

#ifdef SUMOMINI
    Serial.begin(9600);
#endif

    initMotors();
    initOpponentSensors();
    initEdgeSensors();
}

void loop()
{
    handleWSData();
    processEvents();
}