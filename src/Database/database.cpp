#include "database.h"

#include <algorithm> // TODO: implement sort

Database::Database()
    : tablePlayers(TOTAL_PLAYERS),
      tablePlayersRatings(TOTAL_PLAYERS),
      tableUserRatings(TOTAL_USERS)
{
    Timer timer;

    std::ifstream playersFile(PLAYERS_CSV);
    aria::csv::CsvParser playersParser(playersFile);

    for (auto it = ++playersParser.begin(); it != playersParser.end(); ++it)
    {
        auto &row = (*it);
        uint32_t fifaID = misc::atoui(row[0].c_str());

        auto &name = row[1];
        auto &positions = row[2];

        tablePlayers.emplace(fifaID, Player{fifaID, name.c_str(), positions.c_str()});

        tablePlayersRatings.emplace(fifaID, fifaID);
    }
    playersFile.close();

    std::ifstream ratingsFile(RATING_CSV);
    aria::csv::CsvParser ratingsParser(ratingsFile);

    for (auto it = ++ratingsParser.begin(); it != ratingsParser.end(); ++it)
    {
        uint32_t fifaID = misc::atoui((*it)[1].c_str());
        uint32_t userID = misc::atoui((*it)[0].c_str());
        float rating = misc::atof((*it)[2].c_str());

        auto [user, userFound] = tableUserRatings.find(userID);
        auto [player, playerFound] = tablePlayersRatings.find(fifaID);

        if (playerFound)
        {
            player->second.addRating(rating);
        }

        if (!userFound)
            user = tableUserRatings.emplace(userID, userID);

        user->second.ratings.emplace_back(fifaID, rating);
    }

    ratingsFile.close();
}

Database::~Database() {}

std::vector<UserSearch> Database::userSearch(uint32_t id)
{
    Timer timer;
    auto [user, userFound] = tableUserRatings.find(id);

    if (!userFound)
        throw;

    auto &ratings = user->second.ratings;
    std::vector<UserSearch> res;
    res.reserve(ratings.size() >= 20 ? 20 : ratings.size());

    // TODO: make own sort
    std::sort(ratings.begin(), ratings.end(), std::greater<UserRating>());

    int i = 0;
    for (auto &&rating : ratings)
    {

        auto [playerRating, playerRatingFound] = tablePlayersRatings.find(rating.fifaID);
        auto [player, playerFound] = tablePlayers.find(rating.fifaID);

        if (!playerFound || !playerRatingFound)
            throw;

        res.emplace_back(UserSearch(player->second, playerRating->second, rating.rating));
        i++;
        if (i == 20)
            break;
    }
    return res;
}