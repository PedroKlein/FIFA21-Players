#pragma once

#include <stdint.h>
#include <parser.hpp>
#include <vector>
#include <array>
#include "../Structs/index.h"
#include "../SearchStructs/index.h"
#include "../Timer/timer.h"
#include "../HashTable/hashTable.h"
#include "../TrieTree/trieTree.h"
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
const size_t TOTAL_POSITIONS = 30;

class Database
{
private:
    HashTable<uint32_t, Player, TOTAL_PLAYERS> tablePlayers;
    HashTable<uint32_t, PlayerRating, TOTAL_PLAYERS> tablePlayersRatings;

    HashTable<uint32_t, User, TOTAL_USERS> tableUserRatings;

    HashTable<std::string, Position, TOTAL_POSITIONS> tablePositions;

    HashTable<std::string, Tag, TOTAL_TAGS> tableTags;

    TrieTree namesTree;

public:
    Database();
    ~Database();

    std::vector<PlayerSearch> playersSearch(std::string str);
    std::vector<UserSearch> userSearch(uint32_t id);
    std::vector<PositionSearch> positionSearch(uint32_t topN, std::string position);
    std::vector<TagsSearch> tagsSearch(const std::vector<std::string> &Tags);

private:
    void readPlayersCSV();
    void readRatingCSV();
    void readTagsCSV();
    void fillTablePositions();
};
