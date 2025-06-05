#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Sensor.h"

namespace gaia::sensor
{
    class SensorManager
    {
    public:
        void addSensor(std::unique_ptr<Sensor> sensor);
        void updateAll(float deltaTime);
        const std::vector<std::unique_ptr<Sensor>> &sensors() const;
        Sensor *findById(const std::string &id);
        bool removeById(const std::string &id);
        void clear();

    private:
        std::vector<std::unique_ptr<Sensor>> sensors_;
    };

} // namespace gaia::sensor
