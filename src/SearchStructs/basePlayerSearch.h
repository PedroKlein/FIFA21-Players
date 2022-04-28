#pragma once

#include <stdint.h>
#include <iostream>
#include <AppCore/JSHelpers.h>
#include "../Structs/players.h"

using namespace ultralight;

struct BasePlayerSearch
{
    uint32_t fifaID;
    std::string name;
    std::string playerPosition;
    float rating;
    size_t count;

    BasePlayerSearch(){};

    BasePlayerSearch(const Player &player, const PlayerRating &playerRating)
        : fifaID(player.fifaID),
          name(player.name),
          playerPosition(player.positions),
          rating(playerRating.rating),
          count(playerRating.count){};

    friend std::ostream &operator<<(std::ostream &out, const BasePlayerSearch &c)
    {
        out << c.fifaID << " "
            << c.name << " "
            << c.playerPosition << " "
            << c.rating << " "
            << c.count << std::endl;
        return out;
    }

    JSObject toJsObject(JSContextRef &context)
    {
        JSObject res;
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("fifaID"), JSValue(fifaID), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("name"), JSValue(name.c_str()), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("positions"), JSValue(playerPosition.c_str()), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("rating"), JSValue(rating), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("count"), JSValue(count), NULL, NULL);
        return res;
    }
};
