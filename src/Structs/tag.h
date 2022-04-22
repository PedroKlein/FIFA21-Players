#pragma once

#include <string>
#include <vector>

struct Tag
{
    std::string tag;
    std::vector<uint32_t> fifaIDs;

    Tag(std::string_view tag)
        : tag(tag) {}
};
