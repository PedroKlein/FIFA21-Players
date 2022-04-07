#include <stdint.h>

#pragma once

namespace misc
{
    uint32_t atoui(const char *str)
    {
        uint32_t val = 0;
        while (*str)
        {
            val = val * 10 + (*str++ - '0');
        }
        return val;
    }
}