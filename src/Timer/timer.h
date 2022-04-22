#pragma once

#include <chrono>
#include <string>
#include <iostream>

struct Timer
{

#ifndef __GNUC__
    std::chrono::steady_clock::time_point start, end;
#else
    std::chrono::_V2::system_clock::time_point start, end;
#endif

    std::chrono::duration<float> duration;
    std::string context{};

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    Timer(std::string_view context) : context(context)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();

        duration = end - start;

        float ms = duration.count() * 1000.0f;

        std::cout << context << " took " << ms << " ms" << std::endl;
    }
};