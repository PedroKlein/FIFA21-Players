#pragma once

#include <stdint.h>
#include <vector>

struct UserRating
{
    uint32_t fifaID;
    float rating;
};

struct User
{
    uint32_t userId;
    std::vector<UserRating> ratings;
};
