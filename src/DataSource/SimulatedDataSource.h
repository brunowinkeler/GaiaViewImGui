#pragma once
#include "IDataSource.h"

namespace gaia::datasource
{
    class SimulatedDataSource : public IDataSource
    {
    public:
        double readValue() override;
        void setLimits(double minLimit, double maxLimit);

    private:
        double minLimit_ = 20.0;
        double maxLimit_ = 25.0;
    };

} // namespace gaia::datasource
