#pragma once

#include <memory>
#include <string_view>

#include "Path.h"
#include "Point.h"

namespace citymap
{

    class Map;

    class Query {
    public:
        Query(PointId, PointId);
        Query(std::string_view, std::string_view, const Map&);
        virtual ~Query() = default;

        PointId from() const noexcept;
        PointId to() const noexcept;
        void from(PointId) noexcept;
        void to(PointId) noexcept;

        virtual constexpr operator PathType() const noexcept = 0;
        virtual constexpr PathType type() const noexcept     = 0;

    private:
        PointId from_, to_;
    };

    using PolymorphicQueryList = std::vector<std::unique_ptr<Query>>;

    class PedestrianQuery final : public Query {
    public:
        PedestrianQuery(PointId, PointId);
        PedestrianQuery(std::string_view, std::string_view, const Map&);
        ~PedestrianQuery() override = default;

        constexpr operator PathType() const noexcept override { return type(); }

        constexpr PathType type() const noexcept override { return PathType::Pedestrian; }
    };

    class CarQuery final : public Query {
    public:
        CarQuery(PointId, PointId);
        CarQuery(std::string_view, std::string_view, const Map&);
        ~CarQuery() override = default;

        constexpr operator PathType() const noexcept override { return type(); }

        constexpr PathType type() const noexcept override { return PathType::Car; }
    };

    class UnifiedQuery {
    public:
        UnifiedQuery(PointId, PointId, PathType);
        UnifiedQuery(std::string_view, std::string_view, const Map&, PathType);
        UnifiedQuery(const Query&);
        UnifiedQuery(const UnifiedQuery&) noexcept;
        UnifiedQuery(UnifiedQuery&&) noexcept;
        ~UnifiedQuery();

        PointId from() const;
        PointId to() const;
        void from(PointId);
        void to(PointId);
        void set(PointId, PointId, PathType);
        void set(std::string_view, std::string_view, const Map&, PathType);
        void set(const Query&);
        Query& get();
        const Query& get() const;
        void toggleType();
        PathType type() const noexcept;
        operator Query&();
        operator const Query&() const;
        operator PathType() const noexcept;
        UnifiedQuery& operator=(const Query&);
        UnifiedQuery& operator=(const UnifiedQuery&) noexcept;
        UnifiedQuery& operator=(UnifiedQuery&&) noexcept;

    private:
        PathType type_;

        union {
            PedestrianQuery pd_;
            CarQuery car_;
        };
    };

}  // namespace citymap