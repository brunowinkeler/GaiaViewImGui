#pragma once
#include "IDataSource.h"

namespace gaia::datasource
{
    class SimulatedDataSource : public IDataSource
    {
    public:
        double readValue() override;
    };

} // namespace gaia::datasource
