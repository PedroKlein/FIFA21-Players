#include <stdint.h>

struct Player
{
    uint32_t fifaID;
    std::string name;
    std::string positions;

    Player(aria::csv::CsvParser::iterator::value_type csvRow)
    {
        fifaID = (uint32_t)std::stoi(csvRow[0]);
        name = csvRow[1];
        positions = csvRow[2];
    }
};

struct PlayerRating
{
    uint32_t fifaID;
    float rating = 0;
    size_t count = 0;

    PlayerRating(uint32_t fifaID)
    {
        this->fifaID = fifaID;
    }

    void addRating(float rating)
    {
        count++;
        this->rating = (this->rating + rating) / 2.;
    }
};
