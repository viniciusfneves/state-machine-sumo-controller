#if !defined(STRATEGIES_HPP)
#define STRATEGIES_HPP

// Estratégias iniciais
enum class InitialMove
{
    none,
    full_frente,
    zig_zag,
    delayed_radar,
    short_right_arch
};

// Estratégias de busca
enum class Search
{
    none,
    radar
};

// Estratégias de perseguição
enum class Chase
{
    standard
};

// Modos de operação
enum class Mode{
    Auto,
    RC
};

#endif // STRATEGIES_HPP
