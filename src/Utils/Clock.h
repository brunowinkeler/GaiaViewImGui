// src/Utils/Clock.h
#pragma once
#include <chrono>

namespace gaia::utils
{

    class Clock
    {
    public:
        static double now()
        {
            using namespace std::chrono;
            auto now = system_clock::now().time_since_epoch();
            return duration_cast<duration<double>>(now).count();
        }
    };

} // namespace gaia::utils