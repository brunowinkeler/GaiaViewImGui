#pragma once
#include <string>

#include "SensorStatus.h"

namespace gaia::sensor
{
    class Sensor
    {
    public:
        Sensor(std::string id, std::string name, std::string unit, float minValue,
               float maxValue)
            : id_(std::move(id)),
              name_(std::move(name)),
              unit_(std::move(unit)),
              minValue_(minValue),
              maxValue_(maxValue),
              value_(0.0f),
              status_(SensorStatus::OK) {}

        virtual ~Sensor() = default;
        virtual void update(float deltaTime) = 0;

        // Getters
        const std::string &id() const { return id_; }
        const std::string &name() const { return name_; }
        const std::string &unit() const { return unit_; }
        float value() const { return value_; }
        float minValue() const { return minValue_; }
        float maxValue() const { return maxValue_; }
        SensorStatus status() const { return status_; }

    protected:
        void setValue(float val) { value_ = val; }
        void setStatus(SensorStatus st) { status_ = st; }

    private:
        std::string id_;
        std::string name_;
        std::string unit_;
        float value_;
        float minValue_;
        float maxValue_;
        SensorStatus status_;
    };
} // namespace gaia::sensor
