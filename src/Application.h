#pragma once
#include <memory>
#include "Sensor/SensorManager.h"

namespace gaia
{
    class Application
    {
    public:
        Application();
        void run();

    private:
        std::unique_ptr<sensor::SensorManager> sensorManager_;
    };

} // namespace gaia
