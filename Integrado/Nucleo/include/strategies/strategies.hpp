#pragma once

#ifdef ESP32_ENV
using std::vector;

vector<String> modesAvailable       = {"auto", "rc"};
vector<String> initialStrategies    = {"none", "full_frente", "zig_zag"};
vector<String> searchStrategies     = {"none", "radar", "full_teste"};
vector<String> chaseStrategies      = {"standard"};

#endif

// Modos de operação
enum class Mode {
    Auto,
    RC
};

// Estratégias iniciais
enum class InitialMove {
    none,
    full_frente,
    zig_zag
};

// Estratégias de busca
enum class Search {
    none,
    radar, 
    full_teste
};

// Estratégias de perseguição
enum class Chase {
    standard
};
