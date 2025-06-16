#include "Application.h"
#include "Sensor/TemperatureSensor.h"
#include "DataSource/SimulatedDataSource.h"

namespace gaia
{

    Application::Application()
    {
        sensorManager_.addSensor(std::make_unique<sensor::TemperatureSensor>(
            "temp1", "Main Temp", "C", 15.0f, 30.0f, 0.5,
            std::make_unique<datasource::SimulatedDataSource>()));
        gui_.init("GaiaView", 1280, 720);
    }

    void Application::run()
    {
        while (gui_.processEvents())
        {
            sensorManager_.updateAll();
            gui_.beginFrame();
            gui_.plot(sensorManager_);
            gui_.endFrame();
        }
    }

} // namespace gaia