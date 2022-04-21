#include <iostream>
#include "Database/database.h"

int main(int argc, char const *argv[])
{
    Database database;

    auto userSearch = database.userSearch(12389);

    for (auto &&i : userSearch)
    {
        std::cout << i;
    }

    std::vector<std::string> tags = {"Dribbler", "Brazil", "Acrobat"};
    auto tagsSearch = database.tagsSearch(tags);

    for (auto &&i : tagsSearch)
    {
        std::cout << i;
    }

    return 0;
}
