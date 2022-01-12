#pragma once

#ifndef WEBOTS
using std::vector;

vector<String> modesAvailable       = {"auto", "rc"};
vector<String> initialStrategies    = {"none", "full_frente", "zig_zag"};
vector<String> searchStrategies     = {"none", "radar"};
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
    zig_zag,
    delayed_radar,
    short_right_arch
};

// Estratégias de busca
enum class Search {
    none,
    radar
};

// Estratégias de perseguição
enum class Chase {
    standard
};
