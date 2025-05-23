#include "Map.h"

#include <algorithm>

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
    points_.at(a).connections.insert(b);
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

Point& citymap::Map::valueOf(std::string_view name) {
    return valueOf(idOf(name));
}

const Point& citymap::Map::valueOf(std::string_view name) const {
    return valueOf(idOf(name));
}

Point& citymap::Map::valueOf(PointId id) {
    return points_.at(id).val;
}

const Point& citymap::Map::valueOf(PointId id) const {
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

std::string Map::describe(const Path::PointList& pl, const char* sep = ", ") const {
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