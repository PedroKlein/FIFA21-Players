#pragma once

#include <stdint.h>
#include <iostream>
#include "../Players/players.h"

struct TagsSearch
{
    uint32_t fifaID;
    std::string name;
    std::string playerPosition;
    float rating;
    size_t count;

    TagsSearch(){};

    TagsSearch(Player player, PlayerRating playerRating)
        : fifaID(player.fifaID),
          name(player.name),
          playerPosition(player.positions),
          rating(playerRating.rating),
          count(playerRating.count){};

    friend std::ostream &operator<<(std::ostream &out, const TagsSearch &c)
    {
        out << c.fifaID << " "
            << c.name << " "
            << c.playerPosition << " "
            << c.rating << " "
            << c.count << std::endl;
        return out;
    }
};
