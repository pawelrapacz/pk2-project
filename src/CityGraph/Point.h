#pragma once
#include "metrics.h"

namespace citymap
{
    struct Point : public metrics::Point2
    {
        Point() = default;
        Point(int x, int y) : Point2(x, y) {}
        ~Point() = default;
    };
} // namespace citymap