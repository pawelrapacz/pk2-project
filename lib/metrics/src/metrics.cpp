#include "metrics.h"

#include <cmath>

double metrics::euclidean(Point2 a, Point2 b) {
    // return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return std::hypot((a.x - b.x), (a.y - b.y));
}

double metrics::manhattan(Point2 a, Point2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

double metrics::euclidean(Point3 a, Point3 b) {
    // return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
    return std::hypot((a.x - b.x), (a.y - b.y), (a.z - b.z));
}

double metrics::manhattan(Point3 a, Point3 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
}