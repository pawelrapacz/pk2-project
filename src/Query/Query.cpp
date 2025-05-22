#include "Query.h"

#include <stdexcept>

#include "Map.h"

using namespace citymap;

Query::Query(PointId from, PointId to)
    : from_(from), to_(to) {}

Query::Query(std::string_view from, std::string_view to, const Map& map)
    : Query(map.idOf(from), map.idOf(to)) {}

PointId Query::from() const noexcept {
    return from_;
}

PointId Query::to() const noexcept {
    return to_;
}

void Query::from(PointId id) noexcept {
    from_ = id;
}

void Query::to(PointId id) noexcept {
    to_ = id;
}

PedestrianQuery::PedestrianQuery(PointId from, PointId to)
    : Query(from, to) {}

PedestrianQuery::PedestrianQuery(std::string_view from, std::string_view to, const Map& map)
    : Query(from, to, map) {}

CarQuery::CarQuery(PointId from, PointId to)
    : Query(from, to) {}

CarQuery::CarQuery(std::string_view from, std::string_view to, const Map& map)
    : Query(from, to, map) {}

UnifiedQuery::UnifiedQuery(PointId from, PointId to, PathType type = PathType::Car)
    : type_(type) {
    switch (type) {
        case PathType::Car:
            car_ = {from, to};
            break;
        case PathType::Pedestrian:
            pd_ = {from, to};
            break;
        default:
            throw std::logic_error("No suitable type.");
    }
}

UnifiedQuery::UnifiedQuery(std::string_view from, std::string_view to, const Map& map,
                           PathType type = PathType::Car)
    : UnifiedQuery(map.idOf(from), map.idOf(to), type) {}

UnifiedQuery::UnifiedQuery(const Query& other) {
    type_ = other.type();
    switch (type_) {
        case PathType::Car:
            car_ = static_cast<const CarQuery&>(other);
            // car_ = dynamic_cast<const CarQuery&>(other);
            break;
        case PathType::Pedestrian:
            pd_ = static_cast<const PedestrianQuery&>(other);
            // pd_ = dynamic_cast<const PedestrianQuery&>(other);
            break;
        default:
            throw std::logic_error("No suitable type.");
    }
}

UnifiedQuery::UnifiedQuery(const UnifiedQuery& other) noexcept
    : type_(other.type_) {
    switch (type_) {
        case PathType::Car:
            car_ = other.car_;
            break;
        case PathType::Pedestrian:
            pd_ = other.pd_;
            break;
    }
}

UnifiedQuery::UnifiedQuery(UnifiedQuery&& other) noexcept
    : type_(other.type_) {
    switch (type_) {
        case PathType::Car:
            car_ = other.car_;
            break;
        case PathType::Pedestrian:
            pd_ = other.pd_;
            break;
    }
}

UnifiedQuery::~UnifiedQuery() {
    get().~Query();
}

PointId UnifiedQuery::from() const {
    return get().from();
}

PointId UnifiedQuery::to() const {
    return get().to();
}

void UnifiedQuery::from(PointId id) {
    get().from(id);
}

void UnifiedQuery::to(PointId id) {
    get().to(id);
}

void UnifiedQuery::set(PointId from, PointId to, PathType type) {
    get().from(from);
    get().to(to);
    if (type != *this) toggleType();
}

void UnifiedQuery::set(std::string_view from, std::string_view to, const Map& map, PathType type) {
    set(map.idOf(from), map.idOf(to), type);
}

void UnifiedQuery::set(const Query& other) {
    type_ = other.type();
    switch (type_) {
        case PathType::Car:
            car_ = static_cast<const CarQuery&>(other);
            // car_ = dynamic_cast<const CarQuery&>(other);
            break;
        case PathType::Pedestrian:
            pd_ = static_cast<const PedestrianQuery&>(other);
            // pd_ = dynamic_cast<const PedestrianQuery&>(other);
            break;
        default:
            throw std::logic_error("No suitable type.");
    }
}

Query& UnifiedQuery::get() {
    switch (type_) {
        case PathType::Car:
            return car_;
        case PathType::Pedestrian:
            return pd_;
        default:
            throw std::logic_error("No suitable type.");
    }
}

const Query& UnifiedQuery::get() const {
    switch (type_) {
        case PathType::Car:
            return car_;
        case PathType::Pedestrian:
            return pd_;
        default:
            throw std::logic_error("No suitable type.");
    }
}

void UnifiedQuery::toggleType() {
    switch (type_) {
        case PathType::Car:
            pd_ = {car_.from(), car_.to()};
            break;
        case PathType::Pedestrian:
            car_ = {pd_.from(), pd_.to()};
            break;
        default:
            throw std::logic_error("No suitable type.");
    }
}

PathType UnifiedQuery::type() const noexcept {
    return type_;
}

UnifiedQuery::operator Query&() {
    return get();
}

UnifiedQuery::operator const Query&() const {
    return get();
}

UnifiedQuery::operator PathType() const noexcept {
    return type_;
}

UnifiedQuery& UnifiedQuery::operator=(const Query& other) {
    set(other);
    return *this;
}

UnifiedQuery& UnifiedQuery::operator=(const UnifiedQuery& other) noexcept {
    type_ = other.type_;
    switch (type_) {
        case PathType::Car:
            car_ = other.car_;
            break;
        case PathType::Pedestrian:
            pd_ = other.pd_;
            break;
    }
    return *this;
}

UnifiedQuery& citymap::UnifiedQuery::operator=(UnifiedQuery&& other) noexcept {
    type_ = other.type_;
    switch (type_) {
        case PathType::Car:
            car_ = other.car_;
            break;
        case PathType::Pedestrian:
            pd_ = other.pd_;
            break;
    }
    return *this;
}