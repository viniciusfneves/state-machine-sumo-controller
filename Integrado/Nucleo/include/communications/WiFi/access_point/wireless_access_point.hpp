#ifndef WIFI_ACESS_POINT_HPP
#define WIFI_ACESS_POINT_HPP

#include <WiFi.h>

const char *ssid = "ESP32";        // Nome da rede - SSID
const char *password = "12345678"; // Senha da rede

// Realiza as configurações necessárias para a parte de comunicação do ESP32 
void initAccessPoint()
{
    // Cria a rede Wi-Fi própria do ESP com os parametros de nome da rede e senha
    WiFi.softAP(ssid, password);
    delay(100);
}

#endif