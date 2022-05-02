#pragma once

#include <stdint.h>
#include <iostream>
#include <AppCore/JSHelpers.h>
#include "../Structs/players.h"
#include "../Structs/user.h"

struct UserSearch
{
    uint32_t fifaID;
    std::string name;
    float globalRating;
    size_t count;
    float rating;

    UserSearch(){};

    UserSearch(const Player &player, const PlayerRating &playerRating, float userRating)
        : fifaID(player.fifaID),
          name(player.name),
          globalRating(playerRating.rating),
          count(playerRating.count),
          rating(userRating){};

    friend std::ostream &operator<<(std::ostream &out, const UserSearch &c)
    {
        out << c.fifaID << " "
            << c.name << " "
            << c.globalRating << " "
            << c.count << " "
            << c.rating << std::endl;
        return out;
    }

    JSObject toJsObject(JSContextRef &context)
    {
        JSObject res;
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("fifaID"), JSValue(fifaID), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("name"), JSValue(name.c_str()), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("globalRating"), JSValue(globalRating), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("count"), JSValue(count), NULL, NULL);
        JSObjectSetProperty(context, res, JSStringCreateWithUTF8CString("rating"), JSValue(rating), NULL, NULL);
        return res;
    }
};
