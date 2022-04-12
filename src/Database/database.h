#pragma once

#include <stdint.h>
#include <parser.hpp>
#include "../Timer/timer.h"
#include "../HashTable/hashTable.h"
#include "../User/user.h"
#include "../Players/players.h"
#include "../Misc/misc.h"

const size_t TOTAL_PLAYERS = 18945;
const size_t TOTAL_USERS = 110052; // check

class Database
{
private:
    HashTable<Player> tablePlayers;
    HashTable<PlayerRating> tablePlayersRatings;

    HashTable<User> tableUserRatings;

public:
    Database();
    ~Database();
};
