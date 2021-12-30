#ifndef WIFI_ACESS_POINT_HPP
#define WIFI_ACESS_POINT_HPP

#include <WiFi.h>

#include "../../../configuration/specifications.hpp"

const char *ssid = robotSpecifications.robotName;  // Nome da rede - SSID
const char *password = "12345678";                 // Senha da rede

// Realiza as configurações necessárias para a parte de comunicação do ESP32
void initAccessPoint() {
    WiFi.softAP(ssid, password);
    delay(100);
}

void connectToWiFi(const char *ssid, const char *passphrase) {
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
    }
    Serial.print("Connected to adress ");
    Serial.println(WiFi.localIP());
}
#endif