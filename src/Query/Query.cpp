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
            new (&car_) CarQuery(from, to);
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(from, to);
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
            new (&car_) CarQuery(static_cast<const CarQuery&>(other));
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(static_cast<const PedestrianQuery&>(other));
            break;
        default:
            throw std::logic_error("No suitable type.");
    }
}

UnifiedQuery::UnifiedQuery(const UnifiedQuery& other) noexcept
    : type_(other.type_) {
    switch (type_) {
        case PathType::Car:
            new (&car_) CarQuery(other.car_);
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(other.pd_);
            break;
    }
}

UnifiedQuery::UnifiedQuery(UnifiedQuery&& other) noexcept
    : type_(other.type_) {
    switch (type_) {
        case PathType::Car:
            new (&car_) CarQuery(other.car_);
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(other.pd_);
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
    get().~Query();
    type_ = type;
    switch (type) {
        case PathType::Car:
            new (&car_) CarQuery(from, to);
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(from, to);
            break;
        default:
            throw std::logic_error("No suitable type.");
    }
}

void UnifiedQuery::set(std::string_view from, std::string_view to, const Map& map, PathType type) {
    set(map.idOf(from), map.idOf(to), type);
}

void UnifiedQuery::set(const Query& other) {
    set(other.from(), other.to(), other.type());
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
    PointId from = this->from();
    PointId to = this->to();
    get().~Query();
    switch (type_) {
        case PathType::Car:
            type_ = PathType::Pedestrian;
            new (&pd_) PedestrianQuery(from, to);
            break;
        case PathType::Pedestrian:
            type_ = PathType::Car;
            new (&car_) CarQuery(from, to);
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

UnifiedQuery::operator PedestrianQuery&() {
    if (type_ == PathType::Pedestrian)
        return pd_;
    else
        throw std::bad_cast();
}

UnifiedQuery::operator const PedestrianQuery&() const {
    if (type_ == PathType::Pedestrian)
        return pd_;
    else
        throw std::bad_cast();
}

UnifiedQuery::operator CarQuery&() {
    if (type_ == PathType::Car)
        return car_;
    else
        throw std::bad_cast();
}

UnifiedQuery::operator const CarQuery&() const {
    if (type_ == PathType::Car)
        return car_;
    else
        throw std::bad_cast();
}

UnifiedQuery::operator PathType() const noexcept {
    return type_;
}

UnifiedQuery& UnifiedQuery::operator=(const Query& other) {
    set(other);
    return *this;
}

UnifiedQuery& UnifiedQuery::operator=(const UnifiedQuery& other) noexcept {
    get().~Query();
    type_ = other.type_;
    switch (type_) {
        case PathType::Car:
            new (&car_) CarQuery(other.car_);
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(other.pd_);
            break;
    }
    return *this;
}

UnifiedQuery& UnifiedQuery::operator=(UnifiedQuery&& other) noexcept {
    get().~Query();
    type_ = other.type_;
    switch (type_) {
        case PathType::Car:
            new (&car_) CarQuery(other.car_);
            break;
        case PathType::Pedestrian:
            new (&pd_) PedestrianQuery(other.pd_);
            break;
    }
    return *this;
}