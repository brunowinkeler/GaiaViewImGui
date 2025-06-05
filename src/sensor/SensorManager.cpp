#include "SensorManager.h"
#include <algorithm>

namespace gaia::sensor
{
    void SensorManager::addSensor(std::unique_ptr<Sensor> sensor)
    {
        sensors_.push_back(std::move(sensor));
    }

    void SensorManager::updateAll(float deltaTime)
    {
        for (auto &sensor : sensors_)
        {
            sensor->update(deltaTime);
        }
    }

    const std::vector<std::unique_ptr<Sensor>> &SensorManager::sensors() const
    {
        return sensors_;
    }

    Sensor *SensorManager::findById(const std::string &id)
    {
        for (auto &sensor : sensors_)
        {
            if (sensor->id() == id)
            {
                return sensor.get();
            }
        }
        return nullptr;
    }

    bool SensorManager::removeById(const std::string &id)
    {
        auto it = std::remove_if(sensors_.begin(), sensors_.end(),
                                 [&id](const std::unique_ptr<Sensor> &sensor)
                                 {
                                     return sensor->id() == id;
                                 });
        if (it != sensors_.end())
        {
            sensors_.erase(it, sensors_.end());
            return true;
        }
        return false;
    }

    void SensorManager::clear()
    {
        sensors_.clear();
    }

} // namespace gaia::sensor
