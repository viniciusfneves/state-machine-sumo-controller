#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

// Contém todas as estratégias que o robô pode executar
// Utilizado pelos seletores para definir a estratégia a ser utilizada

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

struct Configuration
{
    // Definindo inicialização padrão para as estratégias
    InitialMove initialMove = InitialMove::none;
    Search      search      = Search::none;
    Chase       chase       = Chase::standard;
};

#endif
