#pragma once

#include <cstddef>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "Path.h"
#include "Point.h"
#include "Query.h"
#include "metrics.h"

namespace citymap
{

    class Map {
    public:
        static constexpr PointId npnt = static_cast<PointId>(-1);

        Map()  = default;
        ~Map() = default;

        PointId addPoint(std::string_view, Point);
        PointId addPoint(PointId, std::string_view, Point);
        void removePoint(std::string_view);
        void removePoint(PointId);
        void addConnection(std::string_view, std::string_view);
        void addConnection(PointId, PointId);
        void removeConnection(std::string_view, std::string_view);
        void removeConnection(PointId, PointId);
        bool hasConnection(std::string_view, std::string_view) const;
        bool hasConnection(PointId, PointId) const;
        const std::string& nameOf(PointId) const;
        PointId idOf(std::string_view) const;
        Point& valueOf(std::string_view);
        const Point& valueOf(std::string_view) const;
        Point& valueOf(PointId);
        const Point& valueOf(PointId) const;
        bool contains(PointId) const noexcept;
        bool contains(std::string_view) const noexcept;
        std::size_t size() const;
        bool empty() const noexcept;
        void clear() noexcept;


        std::unique_ptr<Path> findPath(const Query&) const;
        CarPath findCarPath(CarQuery) const;
        PedestrianPath findPedestrianPath(PedestrianQuery) const;
        std::string describe(const Path::PointList&, const char*) const;
        bool isValid(const Path&) const noexcept;

    protected:
        struct PointData {
            PointData() = default;

            PointData(std::string_view name, Point val)
                : name(name), val(val) {}

            ~PointData() = default;

            std::string name;
            Point val;
            std::unordered_set<PointId> connections;
        };

        struct DijkstraData {
            double distance  = std::numeric_limits<double>::infinity();
            PointId previous = npnt;
        };

        using DijkstraResult = std::unordered_map<PointId, DijkstraData>;

        DijkstraResult dijkstra(PointId, metrics::Metric) const;
        static void findPath(PointId, PointId, const DijkstraResult&, Path&);

    private:
        PointId nextId_ {};
        std::unordered_map<PointId, PointData> points_;
        std::unordered_map<std::string_view, PointId> nameIndex_;
    };

}  // namespace citymap