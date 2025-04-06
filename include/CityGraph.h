#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include "Point.h"

namespace citymap
{
    class CityGraph
    {
    public:
        using Edges = std::vector<std::string_view>;
        using key_type = std::string;
        using key_reference = const std::string&;
        using const_key_reference = const std::string&;
        using value_type = Point;
        using size_type = std::size_t;
        
        CityGraph() = default;
        ~CityGraph() = default;

        size_type size() const noexcept;
        void addVertex(key_reference);
        void addVertex(key_reference, value_type);
        void removeVertex(key_reference);
        void addEdge(key_reference, key_reference);
        void removeEdge(key_reference, key_reference);
        bool adjacent(key_reference, key_reference) const;
        const Edges& adjacent(key_reference) const;
        value_type getVertexValue(key_reference) const;
        void setVertexValue(key_reference, value_type);




    private:
        struct VertexData {
            value_type val;
            Edges edges;
        };


        std::unordered_map<std::string, VertexData> vertices_;
    };
} // namespace citymap
