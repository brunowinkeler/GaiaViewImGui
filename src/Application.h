#pragma once
#include <memory>
#include "Sensor/TemperatureSensor.h"

namespace gaia
{

    class Application
    {
    public:
        Application();
        void run();

    private:
        std::unique_ptr<sensor::TemperatureSensor> tempSensor_;
    };

} // namespace gaia
