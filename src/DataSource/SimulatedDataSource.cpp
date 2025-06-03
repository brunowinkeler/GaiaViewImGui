#include "SimulatedDataSource.h"
#include <random>

namespace gaia::datasource
{

    double SimulatedDataSource::readValue()
    {
        static std::default_random_engine engine{std::random_device{}()};
        static std::uniform_real_distribution<double> dist(20.0, 25.0);
        return dist(engine);
    }

} // namespace gaia::datasource
