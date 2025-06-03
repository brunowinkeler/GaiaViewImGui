#pragma once

namespace gaia::datasource
{

    class IDataSource
    {
    public:
        virtual ~IDataSource() = default;
        virtual double readValue() = 0;
    };

} // namespace gaia::datasource
