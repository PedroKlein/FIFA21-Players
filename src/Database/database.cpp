#include "database.h"

Database::Database()
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

        auto userIt = tableUserRatings.find(userID);
        auto playerIt = tablePlayersRatings.find(fifaID);

        if (playerIt != tablePlayersRatings.end())
            playerIt->second.addRating(rating);

        if (userIt != tableUserRatings.end())
            userIt = tableUserRatings.emplace(userID, userID);
        // TODO: segmentation fault after reading from iterator;
        userIt->second.ratings.emplace_back(fifaID, rating);
    }

    ratingsFile.close();
}

Database::~Database()
{
}