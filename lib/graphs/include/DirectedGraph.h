#pragma once

#include "GraphBase.h"

namespace graphs
{

    template<typename Key, typename Value = void>
    class DirectedGraph : public GraphBase<Key, Value> {
    public:
        using typename GraphBase<Key, Value>::key_type;
        using typename GraphBase<Key, Value>::value_type;
        using typename GraphBase<Key, Value>::edge_list;
        using typename GraphBase<Key, Value>::size_type;

        DirectedGraph()  = default;
        ~DirectedGraph() = default;

        void removeVertex(const key_type& vertex) {
            std::ranges::for_each(this->vertices_,
                                  [&vertex](auto& ref) { std::erase(ref.second.edges, vertex); });
            this->vertices_.erase(vertex);
        }

        void addEdge(const key_type& a, const key_type& b) {
            // if constexpr (std::is_pointer<edge_type>) {
            // auto a_ptr = this->vertices_.find(a);
            // }
            // else {
            // this->vertices_.at(a).edges.emplace_back(b);
            // }

            this->vertices_.at(a).edges.emplace_back(b);
        }

        void removeEdge(const key_type& a, const key_type& b) {
            std::erase(this->vertices_.at(a).edges, b);
        }
    };

}  // namespace graphs