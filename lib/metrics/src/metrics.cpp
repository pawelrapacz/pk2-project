#include "metrics.h"
#include <cmath>

inline double metrics::euclidean(citymap::Point a, citymap::Point b) {
    return std::sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}

inline double metrics::manhattan(citymap::Point a, citymap::Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}