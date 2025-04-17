#include "Path.h"
using namespace citymap;


// Path

Path::Path(double distance, const PointList& list)
    : distance_(distance), pathPoints_(list) {}

const Path::PointList &Path::getPathPoints() const noexcept
{ return pathPoints_; }

double Path::getDistance() const noexcept
{ return distance_; }

Path::operator double() const noexcept
{ return distance_; }


// PedestrianPath

PedestrianPath::PedestrianPath(double distance, const PointList& list)
 : Path(distance, list) {}

constexpr PathType PedestrianPath::pathType() const noexcept
{ return PathType::Pedestrian; }

constexpr std::string PedestrianPath::describe() const noexcept
{ return std::string(); }


// CarPath

CarPath::CarPath(double distance, const PointList& list)
 : Path(distance, list) {}

constexpr PathType CarPath::pathType() const noexcept
{ return PathType::Car; }

constexpr std::string CarPath::describe() const noexcept
{ return std::string(); }