#pragma once

#include <stdint.h>
#include <iostream>
#include "../Players/players.h"

struct PositionSearch
{
    uint32_t fifaID;
    std::string name;
    std::string playerPosition;
    float rating;
    size_t count;

    PositionSearch(){};

    PositionSearch(const Player &player, const PlayerRating &playerRating)
        : fifaID(player.fifaID),
          name(player.name),
          playerPosition(player.positions),
          rating(playerRating.rating),
          count(playerRating.count){};

    friend std::ostream &operator<<(std::ostream &out, const PositionSearch &c)
    {
        out << c.fifaID << " "
            << c.name << " "
            << c.playerPosition << " "
            << c.rating << " "
            << c.count << std::endl;
        return out;
    }
};
