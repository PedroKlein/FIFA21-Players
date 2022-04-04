#include <iostream>
#include <hashTable.h>
#include <parser.hpp>
#include <string>

int main(int argc, char const *argv[])
{
    HashTable<std::string> hashTable(18945);

    std::ifstream f("../data/players.csv");
    aria::csv::CsvParser parser(f);

    for (auto it = ++parser.begin(); it != parser.end(); ++it)
    {
        hashTable.insert({(uint32_t)std::stoi((*it)[0]), (*it)[1]});
    }

    if (hashTable.find(155) != hashTable.end())
        std::cout << hashTable.find(155)->value;
    return 0;
}
