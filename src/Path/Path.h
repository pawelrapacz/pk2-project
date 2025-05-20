#pragma once

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "Point.h"

namespace citymap
{

    enum class PathType : unsigned char { Pedestrian, Car };

    class Path {
    public:
        using PointList = std::vector<PointId>;

        Path() = default;
        Path(double, std::initializer_list<PointId>);
        virtual ~Path() = default;

        operator double() const noexcept;
        operator const PointList&() const noexcept;
        double distance() const noexcept;
        const PointList& points() const noexcept;
        PointId from() const noexcept;
        PointId to() const noexcept;

        virtual constexpr PathType type() const noexcept = 0;

    private:
        double distance_;
        PointList points_;

        friend class Map;
    };

    using PolymorphicPathList = std::vector<std::unique_ptr<Path>>;

    class PedestrianPath final : public Path {
    public:
        PedestrianPath() = default;
        PedestrianPath(double, std::initializer_list<PointId>);
        ~PedestrianPath() override = default;

        constexpr PathType type() const noexcept override;
    };

    class CarPath final : public Path {
    public:
        CarPath() = default;
        CarPath(double, std::initializer_list<PointId>);
        ~CarPath() override = default;

        constexpr PathType type() const noexcept override;
    };

}  // namespace citymap