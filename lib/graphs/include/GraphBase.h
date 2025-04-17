#pragma once

#include "graph_traits.h"

#include <unordered_map>
#include <vector>
#include <algorithm>

namespace graph
{
    template<typename Key, typename Value = void>
    class GraphBase
    {
    public:
        using key_type = Key;
        using value_type = Value;
        // using edge_list = std::conditional_t<sizeof(key_type) <= sizeof(void*) && std::is_trivially_destructible_v<key_type>, std::vector<key_type>, std::vector<key_type*>>;
        using edge_list = std::vector<key_type>;

    protected:
        template<typename V, bool = std::is_void_v<V>>
        struct VertexData {
            V val;
            edge_list edges;
        };

        template<typename V>
        struct VertexData<V, true> {
            edge_list edges;
        };

        using edge_type = edge_list::value_type;
        using vertices_map = std::unordered_map<key_type, VertexData<value_type>>;

    public:
        using size_type = vertices_map::size_type;
    public:
        GraphBase() = default;
        ~GraphBase() = default;

        size_type size() const noexcept
        { return vertices_.size(); }

        bool adjacent(const key_type& a, const key_type& b) const
        { return std::ranges::contains(vertices_.at(a).edges, b); }

        const edge_list& adjacent(const key_type& vertex) const
        { return vertices_.at(vertex).edges; }

        bool constains(const key_type& vertex) const
        { return vertices_.contains(vertex); }

        bool empty(const key_type& vertex) const noexcept
        { return vertices_.empty(); }

        void clear() noexcept
        { vertices_.clear(); }

        vertices_map& data() noexcept
        { return vertices_; }

        const vertices_map& data() const noexcept
        { return vertices_; }

        value_type& operator[](const key_type& vertex) {
            static_assert(graph_traits::is_not_void_v<value_type>, "To use this function, value_type cannot be void.");
            return vertices_.at(vertex).val; 
        }

        const value_type& operator[](const key_type& vertex) const {
            static_assert(graph_traits::is_not_void_v<value_type>, "To use this function, value_type cannot be void.");
            return vertices_.at(vertex).val; 
        }

        bool insertVertex(const key_type& newVertex) {
            static_assert(std::is_default_constructible_v<value_type> || std::is_void_v<value_type>, "To use this function, value_type has to be default constructible.");
            return vertices_.try_emplace(newVertex).second; 
        }
    
    
        template<typename V = value_type>
        graph_traits::enable_if_not_void_t<V, bool>
        insertVertex(const key_type& newVertex, V value) {
            return vertices_.insert({newVertex, {value, edge_list()}}).second;
        }
    
        /// TODO: fix VertexData constructor arguments 
        // template<typename... Args>
        // bool emplaceVertex(const key_type& newVertex, Args&& ...args) {
        //     static_assert(not std::is_void_v<value_type>, "Cannot insert a vertex with a value when value_type is void.");
        //     return vertices_.try_emplace(newVertex, std::forward<Args>(args)...).second;
        // }
    
        // template<typename... Args>
        // bool emplaceVertex(const key_type&& newVertex, Args&& ...args) {
        //     static_assert(not std::is_void_v<value_type>, "Cannot insert a vertex with a value when value_type is void.");
        //     return vertices_.try_emplace(newVertex, std::forward<Args>(args)...).second;
        // }
    
        void removeVertex(const key_type& vertex) {
            std::ranges::for_each(vertices_, 
                [&vertex](auto& ref) { std::erase(ref.second.edges, vertex); });
            vertices_.erase(vertex);
        }

    protected:
        vertices_map verticies_;
    };
} // namespace graph