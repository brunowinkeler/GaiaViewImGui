// src/Sensor/Sensor.cpp
#include "Sensor.h"
#include "Utils/Clock.h"

namespace gaia::sensor
{
    void Sensor::tryUpdate()
    {
        double currentTime = gaia::utils::Clock::now();
        if (currentTime - lastUpdateTime_ >= updateInterval_)
        {
            update();
            updated_ = true;
            lastUpdateTime_ = currentTime;
        }
    }

} // namespace gaia::sensor
