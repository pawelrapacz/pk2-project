#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>

#include "Path.h"
#include "Point.h"

namespace citymap
{
    class Map
    {
    public:
        using PointId = std::size_t;
        static constexpr PointId npnt = static_cast<PointId>(-1);

        Map() = default;
        ~Map() = default;

        PointId addPoint(std::string_view, Point);
        PointId addPoint(PointId, std::string_view, Point);
        void removePoint(std::string_view);
        void removePoint(PointId);
        void addConnection(std::string_view, std::string_view);
        void addConnection(PointId, PointId);
        void removeConnection(std::string_view, std::string_view);
        void removeConnection(PointId, PointId);
        
        
        const std::string& nameOf(PointId) const;
        PointId idOf(std::string_view) const;
        bool contains(PointId) const noexcept;
        bool contains(std::string_view) const noexcept;
        std::size_t size() const;
        bool empty() const noexcept;
        void clear() noexcept;
        
        // CarPath findCarPath() const;
        // PedestrianPath findPedestrianPath() const;

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

    private:
        PointId nextId_ { };
        std::unordered_map<PointId, PointData> points_;
        std::unordered_map<std::string_view, PointId> nameIndex_;
    };
    
}  // namespace citymap