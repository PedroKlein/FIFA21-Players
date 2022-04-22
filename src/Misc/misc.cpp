#include "misc.h"

uint32_t misc::atoui(const char *str)
{
    uint32_t val = 0;
    while (*str)
    {
        val = val * 10 + (*str++ - '0');
    }
    return val;
}

float misc::atof(const char *str)
{
    int f, m, sign, d = 1;
    f = m = 0;

    sign = (str[0] == '-') ? -1 : 1;

    if (str[0] == '-' || str[0] == '+')
        str++;

    for (; *str != '.' && *str; str++)
        f = (*str - '0') + f * 10;

    if (*str == '.')
        for (++str; *str; str++)
        {
            m = (*str - '0') + m * 10;
            d *= 10;
        }
    return sign * (f + (float)m / d);
}

std::vector<std::string> misc::splitString(const std::string &str, char delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = 1;
    std::string subStr;
    std::vector<std::string> res;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
    {
        subStr = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        if (str[pos_start] == ' ')
            pos_start++;

        res.push_back(subStr);
    }

    res.push_back(str.substr(pos_start));
    return res;
}