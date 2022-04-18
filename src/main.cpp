#include <iostream>
#include "Database/database.h"

int main(int argc, char const *argv[])
{
    Database database;

    auto res = database.userSearch(12389);

    for (auto &&i : res)
    {
        std::cout << i;
    }

    return 0;
}
