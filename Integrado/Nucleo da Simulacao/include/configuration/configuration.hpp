#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

enum class InitialMove
{
    none
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
    InitialMove initialMove{InitialMove::none};
    Search search{Search::none};
    Chase chase{Chase::standard};
};

#endif
