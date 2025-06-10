// src/Sensor/TemperatureSensor.h
#pragma once
#include "Sensor.h"
#include <memory>
#include "DataSource/IDataSource.h"

namespace gaia::sensor
{

    class TemperatureSensor : public Sensor
    {
    public:
        TemperatureSensor(std::string id, std::string name, std::string unit,
                          float minValue, float maxValue, double updateInterval,
                          std::unique_ptr<gaia::datasource::IDataSource> source);

    protected:
        void update() override;

    private:
        std::unique_ptr<gaia::datasource::IDataSource> source_;
    };

} // namespace gaia::sensor
