#include <iostream>
#include <string>
#include <chrono>
#include <parser.hpp>
#include "HashTable/hashTable.h"
#include "Players/players.h"

int main(int argc, char const *argv[])
{
    auto t1 = std::chrono::high_resolution_clock::now();

    HashTable<Player> tablePlayers(18945);
    HashTable<PlayerRating> tablePlayersRatings(18945);

    std::ifstream playersFile("../data/players.csv");
    aria::csv::CsvParser playersParser(playersFile);

    std::ifstream ratingsFile("../data/rating.csv");
    aria::csv::CsvParser ratingsParser(ratingsFile);

    for (auto it = ++playersParser.begin(); it != playersParser.end(); ++it)
    {
        Player player(*it); // unecessary copy
        tablePlayers.insert({player.fifaID, player});
        PlayerRating playerRating(player.fifaID); // unecessary copy
        tablePlayersRatings.insert({player.fifaID, playerRating});
    }

    for (auto it = ++ratingsParser.begin(); it != ratingsParser.end(); ++it)
    {
        uint32_t fifaID = (uint32_t)std::stoi((*it)[1]);
        auto player = tablePlayersRatings.find(fifaID);

        if (player != tablePlayersRatings.end())
        {
            float rating = std::stof((*it)[2]);
            player->value.addRating(rating);
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // test
    auto player = tablePlayers.find(231747);
    if (player != tablePlayers.end())
    {
        auto rating = tablePlayersRatings.find(player->value.fifaID);
        if (rating != tablePlayersRatings.end())
            std::cout << "\tsofifa_id "
                      << "\tname"
                      << "\tplayer_positions"
                      << "\trating: "
                      << "\tcount" << std::endl;
        std::cout << "\t" << player->value.fifaID
                  << "\t " << player->value.name
                  << "\t " << player->value.positions
                  << "\t " << rating->value.rating
                  << "\t " << rating->value.count << std::endl;
    }

    

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)/1000.;
    std::cout << ms_int.count() << "s\n";

    return 0;
}
