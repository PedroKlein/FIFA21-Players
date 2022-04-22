#pragma once

#include <string>
#include <vector>

struct Position
{
    std::string position;
    std::vector<uint32_t> fifaIDs;

    Position(std::string_view position)
        : position(position) {}
};
