#pragma once

#include <vector>
#include <string>

namespace citymap
{
    enum class PathType : unsigned char {
        Pedestrian,
        Car
    };
    
    class Path
    {
    public:
        using PointList = std::vector<std::string>;
    public:
        Path(double, const PointList&);

        virtual ~Path() = default;
        
        virtual std::string describe() const = 0;

        virtual constexpr PathType pathType() const noexcept = 0;
        
        const PointList& getPathPoints() const noexcept;

        double getDistance() const noexcept;

        operator double() const noexcept;

    private:
        double distance_;
        PointList pathPoints_;
    };
    

    class PedestrianPath final 
      : public Path
    {
    public:
        PedestrianPath(double, const PointList&);
        ~PedestrianPath() override = default;
        
        constexpr PathType pathType() const noexcept override;
        constexpr std::string describe() const noexcept override;
    };


    class CarPath final 
      : public Path
      {
        public:
        CarPath(double, const PointList&);
        ~CarPath() override = default;

        constexpr PathType pathType() const noexcept override;
        constexpr std::string describe() const noexcept override;
    };
} // namespace citymap
