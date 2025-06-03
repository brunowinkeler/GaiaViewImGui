#pragma once
#include "Sensor.h"
#include <memory>
#include "DataSource/IDataSource.h"

namespace gaia::sensor
{

    class TemperatureSensor : public Sensor
    {
    public:
        TemperatureSensor(std::string id,
                          std::string name,
                          std::string unit,
                          float minValue,
                          float maxValue,
                          std::unique_ptr<gaia::datasource::IDataSource> source);

        void update(float deltaTime) override;

    private:
        std::unique_ptr<gaia::datasource::IDataSource> source_;
    };

} // namespace gaia::sensor
