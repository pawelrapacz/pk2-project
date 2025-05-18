#pragma once

namespace metrics
{

    struct Point2 {
        int x, y;
    };

    inline double euclidean(Point2, Point2);

    inline double manhattan(Point2, Point2);

}  // namespace metrics
