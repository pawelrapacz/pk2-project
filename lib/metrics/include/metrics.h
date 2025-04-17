#pragma once

#include "../../../src/CityGraph/Point.h" // needs fixing

namespace metrics
{
    inline double euclidean(citymap::Point,  citymap::Point);

    inline double manhattan(citymap::Point, citymap::Point);
} // namespace metrics
