#include "Application.h"
#include "DataSource/SimulatedDataSource.h"
#include "Sensor/TemperatureSensor.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace gaia
{
    Application::Application()
    {
        sensorManager_ = std::make_unique<sensor::SensorManager>();
        sensorManager_->addSensor(std::make_unique<sensor::TemperatureSensor>(
            "temp1", "Main Temp", "C", 15.0f, 30.0f, std::make_unique<datasource::SimulatedDataSource>()));
    }

    void Application::run()
    {
        while (true)
        {
            sensorManager_->updateAll(0.5f);
            for (const auto &sensor : sensorManager_->sensors())
            {
                std::cout << sensor->id() << ": " << sensor->value() << sensor->unit() << "\n";
            }
        }
    }

} // namespace gaia
