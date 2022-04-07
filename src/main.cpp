#include <iostream>
#include <string>
#include <chrono>
#include <parser.hpp>
#include "HashTable/hashTable.h"
#include "Players/players.h"
#include "Misc/fastConversions.h"

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
        auto row = (*it);
        uint32_t fifaID = misc::atoui(row[0].c_str());

        tablePlayers.emplace(fifaID, (Player){fifaID, row[1], row[2]});

        tablePlayersRatings.emplace(fifaID, (PlayerRating){fifaID});
    }

    for (auto it = ++ratingsParser.begin(); it != ratingsParser.end(); ++it)
    {
        uint32_t fifaID = misc::atoui((*it)[1].c_str());
        auto player = tablePlayersRatings.find(fifaID);

        if (player != tablePlayersRatings.end())
        {
            float rating = atof((*it)[2].c_str());
            player->second.addRating(rating);
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // test
    auto player = tablePlayers.find(231747);
    if (player != tablePlayers.end())
    {
        auto rating = tablePlayersRatings.find(player->second.fifaID);
        if (rating != tablePlayersRatings.end())
            std::cout << "\tsofifa_id "
                      << "\tname"
                      << "\tplayer_positions"
                      << "\trating: "
                      << "\tcount" << std::endl;
        std::cout << "\t" << player->second.fifaID
                  << "\t " << player->second.name
                  << "\t " << player->second.positions
                  << "\t " << rating->second.rating
                  << "\t " << rating->second.count << std::endl;
    }

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) / 1000.;
    std::cout << ms_int.count() << "s\n";

    return 0;
}
