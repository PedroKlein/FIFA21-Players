#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include "sort.h"

namespace misc
{
    uint32_t atoui(const char *str);

    float atof(const char *str);

    std::vector<std::string> splitString(const std::string &str, char delimiter);
}