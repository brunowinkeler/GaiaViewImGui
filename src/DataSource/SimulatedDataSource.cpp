#include "SimulatedDataSource.h"
#include <random>

namespace gaia::datasource
{

    double SimulatedDataSource::readValue()
    {
        static std::default_random_engine engine{std::random_device{}()};
        static std::uniform_real_distribution<double> dist(minLimit_, maxLimit_);
        return dist(engine);
    }

    void SimulatedDataSource::setLimits(double minLimit, double maxLimit)
    {
        minLimit_ = minLimit;
        maxLimit_ = maxLimit;
    }

} // namespace gaia::datasource
