#pragma once

#include <string>
#include <stdint.h>

struct Player
{
    uint32_t fifaID;
    std::string name;
    std::string positions;

    Player(uint32_t fifaID, std::string name, std::string positions)
        : fifaID(fifaID),
          name(name),
          positions(positions) {}
};

struct PlayerRating
{
    uint32_t fifaID;
    float rating = 0;
    size_t count = 0;

    PlayerRating(uint32_t fifaID)
        : fifaID(fifaID) {}

    void addRating(float rating)
    {
        count++;
        this->rating = (this->rating + rating) / 2.f;
    }
};
