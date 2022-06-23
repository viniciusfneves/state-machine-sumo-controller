#pragma once

#include <WiFi.h>

#include <configuration/specifications.hpp>

const char *ssid     = robotSpecifications.robotName;  // Nome da rede - SSID
const char *password = "12345678";                     // Senha da rede

// Realiza as configurações necessárias para a parte de comunicação do ESP32
void initAccessPoint() {
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(ssid, password);
}

void connectToWiFi(const char *ssid, const char *passphrase) {
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(ssid, passphrase);
}