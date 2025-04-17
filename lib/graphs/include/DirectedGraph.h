#pragma once

#include "GraphBase.h"

namespace graphs
{
    template<typename Key, typename Value = void>
    class DirectedGraph : public GraphBase
    {
    public:
        DirectedGraph() = default;
        ~DirectedGraph() = default;

    
        void removeVertex(const key_type& vertex) {
            std::ranges::for_each(vertices_, 
                [&vertex](auto& ref) { std::erase(ref.second.edges, vertex); });
            vertices_.erase(vertex);
        }
    
        void addEdge(const key_type& a, const key_type& b) {
            // if constexpr (std::is_pointer<edge_type>) {
            //     auto a_ptr = vertices_.find(a);
            // }
            // else {
            //     vertices_.at(a).edges.emplace_back(b);
            // }
    
            vertices_.at(a).edges.emplace_back(b);
        }
    
        void removeEdge(const key_type& a, const key_type& b) {
            std::erase(vertices_.at(a).edges, b);
        }
    
    private:
        vertices_map vertices_;
    };
} // namespace graphs