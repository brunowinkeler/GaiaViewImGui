// src/Sensor/Sensor.h
#pragma once
#include <string>
#include "SensorStatus.h"

namespace gaia::sensor
{

    class Sensor
    {
    public:
        Sensor(std::string id, std::string name, std::string unit,
               float minValue, float maxValue, double updateInterval)
            : id_(std::move(id)), name_(std::move(name)), unit_(std::move(unit)),
              minValue_(minValue), maxValue_(maxValue), value_(0.0f), status_(SensorStatus::OK),
              updateInterval_(updateInterval), lastUpdateTime_(0.0) {}

        virtual ~Sensor() = default;
        virtual void tryUpdate();
        double lastUpdateTime() const { return lastUpdateTime_; }
        void resetUpdated() { updated_ = false; }
        bool wasUpdated() const { return updated_; }

        const std::string &id() const { return id_; }
        const std::string &name() const { return name_; }
        const std::string &unit() const { return unit_; }
        float value() const { return value_; }
        float minValue() const { return minValue_; }
        float maxValue() const { return maxValue_; }
        SensorStatus status() const { return status_; }
        double updateInterval() const { return updateInterval_; }

    protected:
        virtual void update() = 0;
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
        double updateInterval_; // seconds between updates
        double lastUpdateTime_; // last update time in seconds
        bool updated_ = false;
    };

} // namespace gaia::sensor
