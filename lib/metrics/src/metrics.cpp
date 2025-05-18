#include "metrics.h"

#include <cmath>

inline double metrics::euclidean(Point2 a, Point2 b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double metrics::manhattan(Point2 a, Point2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}