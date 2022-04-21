#pragma once

#include <stdint.h>
#include <parser.hpp>
#include "./searchStructs.h"
#include "../Timer/timer.h"
#include "../HashTable/hashTable.h"
#include "../User/user.h"
#include "../Players/players.h"
#include "../Tags/tags.h"
#include "../Misc/misc.h"

#ifdef _DEBUG
#define PLAYERS_CSV "../../data/players.csv"
#define RATING_CSV "../../data/minirating.csv"
#else
#define PLAYERS_CSV "../../data/players.csv"
#define RATING_CSV "../../data/rating.csv"
#endif

#define TAGS_CSV "../../data/tags.csv"

const size_t TOTAL_PLAYERS = 18945;
const size_t TOTAL_USERS = 138493; // check
const size_t TOTAL_TAGS = 138493; // check

class Database
{
private:
    HashTable<Player> tablePlayers;
    HashTable<PlayerRating> tablePlayersRatings;

    HashTable<User> tableUserRatings;

    HashTable<Tags> tableTags;

public:
    Database();
    ~Database();

    std::vector<UserSearch> userSearch(uint32_t id);
private:
    void readPlayersCSV();
    void readRatingCSV();
    void readTagsCSV();
};
