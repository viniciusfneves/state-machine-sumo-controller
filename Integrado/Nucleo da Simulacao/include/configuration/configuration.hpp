#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

enum class InitialMove
{
    none,
    full_frente
};
enum class Search
{
    none
};

enum class Chase
{
    standard
};

struct Configuration
{
    // Definindo inicialização padrão para as estratégias
    InitialMove   initialMove     = InitialMove::full_frente;
    Search        search          = Search::none;
    Chase         chase           = Chase::standard;
};

#endif
