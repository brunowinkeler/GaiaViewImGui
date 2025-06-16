#pragma once
#include "Sensor/SensorManager.h"
#include "UI/GuiRenderer.h"

namespace gaia
{
    class Application
    {
    public:
        Application();
        void run();

    private:
        sensor::SensorManager sensorManager_;
        ui::GuiRenderer gui_;
    };

} // namespace gaia