#if !defined(STRATEGIES_HPP)
#define STRATEGIES_HPP

// Estratégias iniciais
enum class InitialMove
{
    none,
    full_frente,
    zig_zag
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

#endif // STRATEGIES_HPP
