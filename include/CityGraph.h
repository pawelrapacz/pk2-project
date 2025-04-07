#pragma once

#include <string>

#include "UndirectedGraph.h"
#include "Point.h"

namespace citymap
{
    using CityGraph = UndirectedGraph<std::string, Point>;
} // namespace citymap
