#pragma once

// Cópia da função map(), porém com suporte à valores do tipo double
double map_double(double x, double in_min, double in_max, double out_min, double out_max) noexcept {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Verifica se um ou mais valores de um Map é true
// (vetor de booleanos) vector -> Vetor à ser analisado
// (int) length -> Tamanho dos vetores
bool checkDetection(const std::map<String, bool>& readings) {
    for (auto element = readings.begin(); element != readings.end(); element++) {
        if (element->second == true) {
            return true;
        }
    }
    return false;
}

// Calcula o erro atralado à leitura dos sensores de acordo com os pesos de cada sensor
// map<String, bool> readings -> Map das leituras dos sensores
// map<String, bool> weights -> Peso dado à leitura de cada sensor
double calculateError(const std::map<String, bool>& readings, std::map<String, double>& weights) {
    double sum              = 0.;
    int    numberOfReadings = 0;
    for (auto value = readings.begin(); value != readings.end(); value++) {
        if (value->second == true) {
            numberOfReadings++;
            sum += weights[value->first];
        }
    }
    return sum / (double)numberOfReadings;
}
