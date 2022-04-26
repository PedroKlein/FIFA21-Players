#pragma once

#include <string>
#include <vector>
#include "../RBTree/rbTree.h"

struct PositionRBKey
{
    uint32_t fifaID;
    float rating;

    friend bool operator==(const PositionRBKey &lhs, const PositionRBKey &rhs)
    {
        return lhs.fifaID == rhs.fifaID;
    }

    friend bool operator>(const PositionRBKey &lhs, const PositionRBKey &rhs)
    {
        return lhs.rating > rhs.rating;
    }

    friend bool operator>=(const PositionRBKey &lhs, const PositionRBKey &rhs)
    {
        return lhs.rating >= rhs.rating;
    }

    friend bool operator<(const PositionRBKey &lhs, const PositionRBKey &rhs)
    {
        return !(lhs >= rhs);
    }

    friend bool operator<=(const PositionRBKey &lhs, const PositionRBKey &rhs)
    {
        return !(lhs > rhs);
    }
};

struct Position
{
    std::string position;
    RBTree<PositionRBKey> fifaIDs;

    Position(std::string_view position)
        : position(position) {}
};
