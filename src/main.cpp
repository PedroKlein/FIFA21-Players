#include <iostream>
#include "Database/database.h"

int main(int argc, char const *argv[])
{
    Database database;

    // test
    // auto player = tablePlayers.find(231747);
    // auto user = tableUserRatings.find(66782);
    // if (player != tablePlayers.end())
    // {
    //     auto rating = tablePlayersRatings.find(player->second.fifaID);
    //     if (rating != tablePlayersRatings.end())
    //     {
    //         std::cout << "\tsofifa_id "
    //                   << "\tname"
    //                   << "\tplayer_positions"
    //                   << "\trating: "
    //                   << "\tcount" << std::endl;
    //         std::cout << "\t" << player->second.fifaID
    //                   << "\t " << player->second.name
    //                   << "\t " << player->second.positions
    //                   << "\t " << rating->second.rating
    //                   << "\t " << rating->second.count << std::endl;
    //     }
    // }

    // if (user != tableUserRatings.end())
    // {
    //     std::cout << "\tsofifa_id "
    //               << "\tname"
    //               << "\tglobal_rating"
    //               << "\tcount"
    //               << "\trating" << std::endl;
    //     for (auto &&rate : user->second.ratings)
    //     {
    //         auto rating = tablePlayersRatings.find(rate.fifaID);
    //         auto player = tablePlayers.find(rate.fifaID);

    //         std::cout << "\t " << player->second.fifaID
    //                   << "\t " << player->second.name
    //                   << "\t " << rating->second.rating
    //                   << "\t " << rating->second.count
    //                   << "\t " << rate.rating

    //                   << std::endl;
    //     }
    // }

    return 0;
}
