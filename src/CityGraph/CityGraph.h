#pragma once

#include <string>

#include "DirectedGraph.h"
#include "Point.h"

namespace citymap
{
    using CityGraph = graphs::DirectedGraph<std::string, Point>;
} // namespace citymap
