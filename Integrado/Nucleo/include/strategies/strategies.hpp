#pragma once

using std::vector;

vector<String> modesAvailable    = {"auto", "rc"};
vector<String> initialStrategies = {"none", "full_frente", "zig_zag", "arco"};
vector<String> searchStrategies  = {"none", "radar", "teco"};
vector<String> chaseStrategies   = {"standard"};

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
    arco
};

// Estratégias de busca
enum class Search {
    none,
    radar,
    teco
};

// Estratégias de perseguição
enum class Chase {
    standard
};
