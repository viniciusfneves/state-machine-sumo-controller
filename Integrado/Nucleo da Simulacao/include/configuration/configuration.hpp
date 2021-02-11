#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

enum class InitialMove
{
    none,
};
enum class Search
{
    none,
};

struct Configuration
{
    InitialMove initialMove{InitialMove::none};
    Search search{Search::none};
};

#endif
