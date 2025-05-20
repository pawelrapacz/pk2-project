#pragma once
#include "metrics.h"
#include <cstddef>

namespace citymap
{
    using PointId = std::size_t;

    struct Point : public metrics::Point2 {
        Point() = default;

        Point(int x, int y)
            : Point2(x, y) {}

        ~Point() = default;
    };

}  // namespace citymap