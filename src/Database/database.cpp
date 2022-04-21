#include "database.h"

Database::Database()
{
    Timer timer("Database_init");

    readPlayersCSV();

    readRatingCSV();

    readTagsCSV();
}

Database::~Database() {}

void Database::readPlayersCSV()
{
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
}

void Database::readRatingCSV()
{
    std::ifstream ratingsFile(RATING_CSV);
    aria::csv::CsvParser ratingsParser(ratingsFile);

    for (auto it = ++ratingsParser.begin(); it != ratingsParser.end(); ++it)
    {
        uint32_t fifaID = misc::atoui((*it)[1].c_str());
        uint32_t userID = misc::atoui((*it)[0].c_str());
        float rating = misc::atof((*it)[2].c_str());

        auto [userIt, userFound] = tableUserRatings.find(userID);
        auto [playerIt, playerFound] = tablePlayersRatings.find(fifaID);

        if (playerFound)
            playerIt->second.addRating(rating);

        if (!userFound)
            userIt = tableUserRatings.emplace(userID, userID);

        userIt->second.ratings.emplace_back(fifaID, rating);
    }

    ratingsFile.close();
}

void Database::readTagsCSV()
{
    std::ifstream tagsFile(TAGS_CSV);
    aria::csv::CsvParser tagsParser(tagsFile);

    for (auto it = ++tagsParser.begin(); it != tagsParser.end(); ++it)
    {
        auto &row = (*it);
        uint32_t fifaID = misc::atoui(row[1].c_str());

        auto &tag = row[2];

        auto [tagIt, tagFound] = tableTags.find(tag);

        if (!tagFound)
            tagIt = tableTags.emplace(tag, tag);

        tagIt->second.fifaIDs.emplace_back(fifaID);
    }

    tagsFile.close();
}

std::vector<UserSearch> Database::userSearch(uint32_t id)
{
    Timer timer("UserSearch");
    auto [user, userFound] = tableUserRatings.find(id);

    if (!userFound)
        throw;

    auto &ratings = user->second.ratings;
    std::vector<UserSearch> res;
    res.reserve(ratings.size() >= 20 ? 20 : ratings.size());

    misc::sort(ratings.begin(), ratings.end(), std::greater<UserRating>());

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

// TODO: improve tag search with a better data struct for fifa ids collection for each tag.
std::vector<TagsSearch> Database::tagsSearch(std::vector<std::string> tags)
{
    Timer timer("TagsSearch");

    if (tags.size() == 0)
        return {};

    std::vector<uint32_t> fifaIDsRes;
    bool first = true;

    for (auto &&tag : tags)
    {
        auto [tagIt, tagFound] = tableTags.find(tag);

        if (!tagFound)
            return {};

        auto &fifaIds = tagIt->second.fifaIDs;

        misc::sort(fifaIds.begin(), fifaIds.end(), std::less<uint32_t>());
        fifaIds.erase(std::unique(fifaIds.begin(), fifaIds.end()), fifaIds.end());

        if (first)
        {
            fifaIDsRes = fifaIds, first = false;
            continue;
        }
        std::vector<uint32_t> newfifaIDsRes;
        std::set_intersection(fifaIds.begin(), fifaIds.end(),
                              fifaIDsRes.begin(), fifaIDsRes.end(),
                              back_inserter(newfifaIDsRes));

        if (newfifaIDsRes.size() == 0)
            return {};

        fifaIDsRes = newfifaIDsRes;
    }

    std::vector<TagsSearch> res;
    res.reserve(fifaIDsRes.size());

    for (auto &&id : fifaIDsRes)
    {

        auto [playerRating, playerRatingFound] = tablePlayersRatings.find(id);
        auto [player, playerFound] = tablePlayers.find(id);

        if (!playerFound || !playerRatingFound)
            throw;

        res.emplace_back(TagsSearch(player->second, playerRating->second));
    }

    return res;
}