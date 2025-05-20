#include "Map.h"
#include <algorithm>

using namespace citymap;

PointId Map::addPoint(std::string_view name, Point val) {
    auto id = nextId_++;
    if (points_.try_emplace(id, name, val).second) {
        nameIndex_.emplace(name, id);
        return id;
    }
    else
        return npnt;
}

PointId Map::addPoint(PointId id, std::string_view name, Point val) {
    if (points_.try_emplace(id, name, val).second) {
        nameIndex_.emplace(name, id);
        if (nextId_ <= id) nextId_ = id + 1;
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
    std::ranges::for_each(points_, [&id](auto& ref) {
        ref.second.connections.erase(id);
    });
}

void Map::removePoint(PointId id) {
    if (!contains(id)) return;
    nameIndex_.erase(points_[id].name);
    points_.erase(id);
    std::ranges::for_each(points_, [&id](auto& ref) {
        ref.second.connections.erase(id);
    });
}

void Map::addConnection(std::string_view a, std::string_view b) {
    addConnection(nameIndex_.at(a), nameIndex_.at(b));
}

void Map::addConnection(PointId a, PointId b) {
    points_.at(a).connections.insert(b);
}

void Map::removeConnection(std::string_view a, std::string_view b) {
    removeConnection(nameIndex_.at(a), nameIndex_.at(b));
}

void Map::removeConnection(PointId a, PointId b) {
    points_.at(a).connections.erase(b);
}

const std::string& Map::nameOf(PointId id) const {
    return points_.at(id).name;
}

PointId Map::idOf(std::string_view name) const {
    return nameIndex_.at(name);
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