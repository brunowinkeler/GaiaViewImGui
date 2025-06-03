#include "TemperatureSensor.h"

namespace gaia::sensor
{

    TemperatureSensor::TemperatureSensor(std::string id,
                                         std::string name,
                                         std::string unit,
                                         float minValue,
                                         float maxValue,
                                         std::unique_ptr<gaia::datasource::IDataSource> source)
        : Sensor(std::move(id), std::move(name), std::move(unit), minValue, maxValue),
          source_(std::move(source)) {}

    void TemperatureSensor::update(float /*deltaTime*/)
    {
        float temp = static_cast<float>(source_->readValue());
        setValue(temp);

        if (temp < minValue() || temp > maxValue())
        {
            setStatus(SensorStatus::Warning);
        }
        else
        {
            setStatus(SensorStatus::OK);
        }
    }

} // namespace gaia::sensor
