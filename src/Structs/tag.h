#pragma once

#include <string>
#include "../RBTree/rbTree.h"

struct Tag
{
    std::string tag;
    RBTree<uint32_t> fifaIDs;

    Tag(std::string_view tag)
        : tag(tag) {}
};
