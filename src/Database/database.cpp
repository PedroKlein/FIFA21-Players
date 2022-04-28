#include "database.h"

Database::Database()
{
    Timer timer("Database_init");

    readPlayersCSV();

    readRatingCSV();

    readTagsCSV();

    fillTablePositions();
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

        this->namesTree.insert(misc::toLower(name), fifaID);
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

        tagIt->second.fifaIDs.insert(fifaID);
    }

    tagsFile.close();
}

void Database::fillTablePositions()
{
    std::ifstream playersFile(PLAYERS_CSV);
    aria::csv::CsvParser playersParser(playersFile);

    for (auto it = ++playersParser.begin(); it != playersParser.end(); ++it)
    {
        auto &row = (*it);
        uint32_t fifaID = misc::atoui(row[0].c_str());

        auto [playerRating, playerRatingFound] = tablePlayersRatings.find(fifaID);

        if (!playerRatingFound)
            throw;

        float &rating = playerRating->second.rating;
        size_t &count = playerRating->second.count;
        rating /= count;

#ifndef _DEBUG
        if (playerRating->second.count < 1000)
            continue;
#endif

        std::vector<std::string> positions = misc::splitString(row[2], ',');

        for (auto &&pos : positions)
        {
            auto [position, positionFound] = tablePositions.find(pos);

            if (!positionFound)
                position = tablePositions.emplace(pos, pos);

            position->second.fifaIDs.insert(PositionRBKey{fifaID, rating});
        }
    }

    playersFile.close();
}

std::vector<BasePlayerSearch> Database::playersSearch(std::string str)
{
    Timer timer("PlayerSearch");

    auto fifaIds = this->namesTree.search(misc::toLower(str));

    std::vector<BasePlayerSearch> res;

    for (auto &&id : fifaIds)
    {

        auto [playerRating, playerRatingFound] = tablePlayersRatings.find(id);
        auto [player, playerFound] = tablePlayers.find(id);

        if (!playerFound || !playerRatingFound)
            throw;

        res.emplace_back(BasePlayerSearch(player->second, playerRating->second));
    }

    return res;
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

        if (++i == 20)
            break;
    }
    return res;
}

std::vector<BasePlayerSearch> Database::positionSearch(uint32_t topN, std::string position)
{
    Timer timer("PositionSearch");
    auto [positionIt, positionFound] = tablePositions.find(position);

    if (!positionFound)
        return {};

    auto &fifaIds = positionIt->second.fifaIDs.getOderedVector();
    std::vector<BasePlayerSearch> res;
    res.reserve(fifaIds.size() >= topN ? topN : fifaIds.size());

    int i = 0;
    for (auto it = fifaIds.rbegin(); it != fifaIds.rend(); ++it)
    {
        auto [playerRating, playerRatingFound] = tablePlayersRatings.find(it->fifaID);
        auto [player, playerFound] = tablePlayers.find(it->fifaID);

        if (!playerFound || !playerRatingFound)
            throw;

        res.emplace_back(BasePlayerSearch(player->second, playerRating->second));

        if (++i == topN)
            break;
    }

    return res;
}

std::vector<BasePlayerSearch> Database::tagsSearch(const std::vector<std::string> &tags)
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

        auto &fifaIds = tagIt->second.fifaIDs.getOderedVector();

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

    std::vector<BasePlayerSearch> res;
    res.reserve(fifaIDsRes.size());

    for (auto &&id : fifaIDsRes)
    {

        auto [playerRating, playerRatingFound] = tablePlayersRatings.find(id);
        auto [player, playerFound] = tablePlayers.find(id);

        if (!playerFound || !playerRatingFound)
            throw;

        res.emplace_back(BasePlayerSearch(player->second, playerRating->second));
    }

    return res;
}