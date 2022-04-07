#include <iostream>
#include <string>
#include <chrono>
#include <parser.hpp>
#include "HashTable/hashTable.h"
#include "Players/players.h"
#include "User/user.h"
#include "Misc/fastConversions.h"

int main(int argc, char const *argv[])
{
    auto t1 = std::chrono::high_resolution_clock::now();

    HashTable<Player> tablePlayers(18945);
    HashTable<PlayerRating> tablePlayersRatings(18945);

    HashTable<User> tableUserRatings(110052);

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
        uint32_t userID = misc::atoui((*it)[0].c_str());
        float rating = atof((*it)[2].c_str());

        auto user = tableUserRatings.find(userID);
        auto player = tablePlayersRatings.find(fifaID);

        if (player != tablePlayersRatings.end())
        {
            player->second.addRating(rating);
        }

        if (user == tableUserRatings.end())
            user = tableUserRatings.emplace(userID, (User){userID});

        user->second.ratings.push_back((UserRating){fifaID, rating});
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // test
    auto player = tablePlayers.find(231747);
    auto user = tableUserRatings.find(66782);
    if (player != tablePlayers.end())
    {
        auto rating = tablePlayersRatings.find(player->second.fifaID);
        if (rating != tablePlayersRatings.end())
        {
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
    }

    if (user != tableUserRatings.end())
    {
        std::cout << "\tsofifa_id "
                  << "\tname"
                  << "\tglobal_rating"
                  << "\tcount"
                  << "\trating" << std::endl;
        for (auto &&rate : user->second.ratings)
        {
            auto rating = tablePlayersRatings.find(rate.fifaID);
            auto player = tablePlayers.find(rate.fifaID);

            std::cout << "\t " << player->second.fifaID
                      << "\t " << player->second.name
                      << "\t " << rating->second.rating
                      << "\t " << rating->second.count
                      << "\t " << rate.rating

                      << std::endl;
        }
    }

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) / 1000.;
    std::cout << ms_int.count() << "s\n";

    return 0;
}
