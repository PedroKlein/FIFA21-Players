#pragma once

#include <string>
#include <vector>

struct Tags
{
    std::string tag;
    std::vector<uint32_t> fifaIDs;

    Tags(std::string_view tag)
        : tag(tag) {}
};
