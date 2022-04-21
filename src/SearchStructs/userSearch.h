#pragma once

#include <stdint.h>
#include <iostream>
#include "../Players/players.h"
#include "../User/user.h"

struct UserSearch
{
    uint32_t fifaID;
    std::string name;
    float globalRating;
    size_t count;
    float rating;

    UserSearch(){};

    UserSearch(Player player, PlayerRating playerRating, float userRating)
        : fifaID(player.fifaID),
          name(player.name),
          globalRating(playerRating.rating),
          count(playerRating.count),
          rating(userRating){};

    friend std::ostream &operator<<(std::ostream &out, const UserSearch &c)
    {
        out << c.fifaID << " "
            << c.name << " "
            << c.globalRating << " "
            << c.count << " "
            << c.rating << std::endl;
        return out;
    }
};
