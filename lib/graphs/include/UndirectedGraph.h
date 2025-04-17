#pragma once

#include "GraphBase.h"

namespace graphs
{
    template<typename Key, typename Value = void>
    class UndirectedGraph : public GraphBase
    {
    public:
        UndirectedGraph() = default;
        ~UndirectedGraph() = default;

    
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
            //     vertices_.at(b).edges.emplace_back(a);
            // }
    
            vertices_.at(a).edges.emplace_back(b);
            vertices_.at(b).edges.emplace_back(a);
        }
    
        void removeEdge(const key_type& a, const key_type& b) {
            std::erase(vertices_.at(a).edges, b);
            std::erase(vertices_.at(b).edges, a);
        }
    
    private:
        vertices_map vertices_;
    };
} // namespace graphs