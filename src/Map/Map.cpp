#include "Map.h"

#include <algorithm>
#include <queue>

using namespace citymap;

PointId Map::addPoint(std::string_view name, Point val) {
    auto id = nextId_++;
    if (auto [it, success] = points_.try_emplace(id, name, val); success) {
        nameIndex_.emplace(it->second.name, id);
        return id;
    }
    else
        return npnt;
}

PointId Map::addPoint(PointId id, std::string_view name, Point val) {
    if (id > nextId_) nextId_ = id + 1;
    if (auto [it, success] = points_.try_emplace(id, name, val); success) {
        nameIndex_.emplace(it->second.name, id);
        return id;
    }
    else
        return npnt;
}

void Map::removePoint(std::string_view name) {
    if (!contains(name)) return;
    PointId id = idOf(name);
    nameIndex_.erase(name);
    points_.erase(id);
    std::ranges::for_each(points_, [&id](auto& ref) { ref.second.connections.erase(id); });
}

void Map::removePoint(PointId id) {
    if (!contains(id)) return;
    nameIndex_.erase(points_[id].name);
    points_.erase(id);
    std::ranges::for_each(points_, [&id](auto& ref) { ref.second.connections.erase(id); });
}

void Map::addConnection(std::string_view a, std::string_view b) {
    addConnection(idOf(a), idOf(b));
}

void Map::addConnection(PointId a, PointId b) {
    if (a != b) points_.at(a).connections.insert(b);
}

void Map::removeConnection(std::string_view a, std::string_view b) {
    removeConnection(idOf(a), idOf(b));
}

void Map::removeConnection(PointId a, PointId b) {
    points_.at(a).connections.erase(b);
}

bool Map::hasConnection(std::string_view a, std::string_view b) const {
    return hasConnection(idOf(a), idOf(b));
}

bool Map::hasConnection(PointId a, PointId b) const {
    return points_.at(a).connections.contains(b);
}

const std::string& Map::nameOf(PointId id) const {
    return points_.at(id).name;
}

PointId Map::idOf(std::string_view name) const {
    return nameIndex_.at(name);
}

Point& Map::valueOf(std::string_view name) {
    return valueOf(idOf(name));
}

const Point& Map::valueOf(std::string_view name) const {
    return valueOf(idOf(name));
}

Point& Map::valueOf(PointId id) {
    return points_.at(id).val;
}

const Point& Map::valueOf(PointId id) const {
    return points_.at(id).val;
}

bool Map::contains(PointId id) const noexcept {
    return points_.contains(id);
}

bool Map::contains(std::string_view name) const noexcept {
    return nameIndex_.contains(name);
}

std::size_t Map::size() const {
    return points_.size();
}

bool Map::empty() const noexcept {
    return points_.empty();
}

void Map::clear() noexcept {
    points_.clear();
    nameIndex_.clear();
    nextId_ = 0;
}

std::unique_ptr<Path> Map::findPath(const Query& query) const {
    if (query.type() == PathType::Pedestrian)
        return std::make_unique<PedestrianPath>(
            findPedestrianPath(static_cast<const PedestrianQuery&>(query)));
    else
        return std::make_unique<CarPath>(findCarPath(static_cast<const CarQuery&>(query)));
}

CarPath Map::findCarPath(CarQuery query) const {
    CarPath path;
    findPath(query.from(), query.to(), dijkstra(query.from(), metrics::manhattan), path);
    return path;
}

PedestrianPath Map::findPedestrianPath(PedestrianQuery query) const {
    PedestrianPath path;
    findPath(query.from(), query.to(), dijkstra(query.from(), metrics::euclidean), path);
    return path;
}

std::string Map::describe(const Path::PointList& pl, const char* sep = ", ") const {
    if (pl.empty()) return std::string();

    std::string output;
    for (std::size_t i = 0; i < pl.size() - 1; i++)
        output += points_.at(pl[i]).name + sep;
    output += points_.at(pl.back()).name;
    return output;
}

bool Map::isValid(const Path& path) const noexcept {
    using Iter = Path::PointList::const_iterator;
    if (path.points_.empty()) return false;
    for (Iter it = path.points_.begin(); it < path.points_.end() - 1; it++)
        if (!hasConnection(*it, *(it + 1))) return false;
    return true;
}

Map::DijkstraResult Map::dijkstra(PointId start, metrics::Metric metric) const {
    DijkstraResult result;
    for (auto& [key, val] : points_)
        result[key];

    auto compFunc = [&result](PointId a, PointId b) -> bool {
        return result[a].distance < result[b].distance;
    };

    std::priority_queue<PointId, std::vector<PointId>, decltype(compFunc)> queue(compFunc);

    result[start] = {0, start};
    queue.push(start);

    while (!queue.empty()) {
        PointId currentPoint = queue.top();
        queue.pop();
        double currentDistance = result[currentPoint].distance;

        for (auto& neighbour : points_.at(currentPoint).connections) {
            double newDistance
                = currentDistance + metric(valueOf(currentPoint), valueOf(neighbour));
            if (newDistance < result[neighbour].distance) {
                result[neighbour] = {newDistance, currentPoint};
                queue.push(neighbour);
            }
        }
    }

    return result;
}

void Map::findPath(PointId from, PointId to, const DijkstraResult& dj, Path& path) {
    path.distance_ = dj.at(to).distance;

    PointId currentPoint = to;
    while (currentPoint != from) {
        path.points_.push_back(currentPoint);
        currentPoint = dj.at(currentPoint).previous;
    }
    path.points_.push_back(from);

    std::ranges::reverse(path.points_);
}