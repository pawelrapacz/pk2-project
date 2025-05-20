#include "Path.h"
using namespace citymap;

// Path

Path::Path(double d, std::initializer_list<PointId> pts)
    : distance_(d), points_(pts) {}

Path::operator double() const noexcept {
    return distance_;
}

Path::operator const Path::PointList&() const noexcept {
    return points_;
}

double Path::distance() const noexcept {
    return distance_;
}

const Path::PointList& Path::points() const noexcept {
    return points_;
}

PointId Path::from() const noexcept {
    return points_.front();
}

PointId Path::to() const noexcept {
    return points_.back();
}

// PedestrianPath

PedestrianPath::PedestrianPath(double d, std::initializer_list<PointId> pts)
    : Path(d, pts) {}

constexpr PathType PedestrianPath::type() const noexcept {
    return PathType::Pedestrian;
}

// CarPath

CarPath::CarPath(double d, std::initializer_list<PointId> pts)
    : Path(d, pts) {}

constexpr PathType CarPath::type() const noexcept {
    return PathType::Car;
}