#include "Application.h"
#include "DataSource/SimulatedDataSource.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace gaia
{

    Application::Application()
    {
        tempSensor_ = std::make_unique<sensor::TemperatureSensor>(
            "temp1",
            "Main Temp",
            "C",
            15.0f,
            30.0f,
            std::make_unique<datasource::SimulatedDataSource>());
    }

    void Application::run()
    {
        while (true)
        {
            tempSensor_->update(0.5f);
            std::cout << "ID: " << tempSensor_->id()
                      << " | Name: " << tempSensor_->name()
                      << " | Value: " << tempSensor_->value() << " " << tempSensor_->unit()
                      << " | Status: " << static_cast<int>(tempSensor_->status())
                      << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

} // namespace gaia
