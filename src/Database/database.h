#pragma once

#include <stdint.h>
#include <parser.hpp>
#include "../Timer/timer.h"
#include "../HashTable/hashTable.h"
#include "../User/user.h"
#include "../Players/players.h"
#include "../Misc/misc.h"

#ifdef _DEBUG
#define PLAYERS_CSV "../../data/players.csv"
#define RATING_CSV "../../data/rating.csv"
#else
#define PLAYERS_CSV "../data/players.csv"
#define RATING_CSV "../data/rating.csv"
#endif

#define RATING_CSV "../../data/rating.csv"
#define MINIRATING_CSV "../data/minirating.csv"
#define TAGS_CSV "../data/tags.csv"

const size_t TOTAL_PLAYERS = 18945;
const size_t TOTAL_USERS = 138493; // check

class Database
{
private:
    HashTable<Player, TOTAL_PLAYERS> tablePlayers;
    HashTable<PlayerRating, TOTAL_PLAYERS> tablePlayersRatings;

    HashTable<User, TOTAL_USERS> tableUserRatings;

public:
    Database();
    ~Database();
};
