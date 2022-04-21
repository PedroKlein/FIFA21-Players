#pragma once

#include <stdint.h>
#include <parser.hpp>
#include <vector>
#include <array>
#include "../SearchStructs/userSearch.h"
#include "../SearchStructs/tagsSearch.h"
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
const size_t TOTAL_TAGS = 937;     // check

class Database
{
private:
    HashTable<uint32_t, Player, TOTAL_PLAYERS> tablePlayers;
    HashTable<uint32_t, PlayerRating, TOTAL_PLAYERS> tablePlayersRatings;

    HashTable<uint32_t, User, TOTAL_USERS> tableUserRatings;

    HashTable<std::string, Tags, TOTAL_TAGS> tableTags;

public:
    Database();
    ~Database();

    std::vector<UserSearch> userSearch(uint32_t id);
    std::vector<TagsSearch> tagsSearch(const std::vector<std::string> &Tags);

private:
    void readPlayersCSV();
    void readRatingCSV();
    void readTagsCSV();
};
