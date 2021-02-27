#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

// Contém todas as estratégias que o robô pode executar
// Utilizado pelos seletores para definir a estratégia a ser utilizada

// Estratégias iniciais
enum class InitialMove
{
    none,
    full_frente
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
    InitialMove   initialMove     = InitialMove::full_frente;
    Search        search          = Search::radar;
    Chase         chase           = Chase::standard;
};

// Objeto global de configurações do robô
Configuration config;
#endif
