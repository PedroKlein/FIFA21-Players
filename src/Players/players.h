#pragma once

#include <stdint.h>

struct Player
{
    uint32_t fifaID;
    std::string name;
    std::string positions;
};

struct PlayerRating
{
    uint32_t fifaID;
    float rating = 0;
    size_t count = 0;

    void addRating(float rating)
    {
        count++;
        this->rating = (this->rating + rating) / 2.;
    }
};
