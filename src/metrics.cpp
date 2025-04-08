#include <metrics.h>
#include <cmath>

using namespace citymap;

inline double metrics::euclidean(Point a, Point b) {
    return std::sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}

inline double metrics::manhattan(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}