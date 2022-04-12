#pragma once

#include <stdint.h>
#include <vector>

struct UserRating
{
    uint32_t fifaID;
    float rating;

    UserRating(uint32_t fifaID, float rating) : fifaID(fifaID), rating(rating)
    {
    }
};

struct User
{
    uint32_t userId;
    std::vector<UserRating> ratings;

    User(uint32_t userId, std::vector<UserRating> &&ratings)
        : userId(userId),
          ratings(std::move(ratings)) {}

    User(uint32_t userId)
        : userId(userId) {}
};
