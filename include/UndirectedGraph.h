#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>

#include "graph_traits.h"


template<typename Key, typename Value = void>
class UndirectedGraph
{
public:
    using key_type = Key;
    using value_type = Value;
    // using edge_list = std::conditional_t<sizeof(key_type) <= sizeof(void*) && std::is_trivially_destructible_v<key_type>, std::vector<key_type>, std::vector<key_type*>>;
    using edge_list = std::vector<key_type>;

private:
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
    UndirectedGraph() = default;
    ~UndirectedGraph() = default;


    size_type size() const noexcept
    { return vertices_.size(); }


    bool insertVertex(const key_type& newVertex) {
        static_assert(std::is_trivially_constructible_v<value_type> || std::is_void_v<value_type>, "To use this function, value_type has to be trivially constructible.");
        return vertices_.try_emplace(newVertex).second; 
    }

    template<typename V = value_type>
    graph_traits::enable_if_not_void_t<V, bool>
    insertVertex(const key_type& newVertex, V value) {
        return vertices_.insert({newVertex, {value, edge_list()}}).second;
    }


    template<typename... Args>
    bool emplaceVertex(const key_type& newVertex, Args&& ...args) {
        static_assert(not std::is_void_v<value_type>, "Cannot insert a vertex with a value when value_type is void.");
        return vertices_.try_emplace(newVertex, std::forward<Args>(args)...).second;
    }


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


    bool adjacent(const key_type& a, const key_type& b) const
    { return std::ranges::contains(vertices_.at(a).edges, b); }


    const edge_list& adjacent(const key_type& vertex) const
    { return vertices_.at(vertex).edges; }


    value_type getVertexValue(const key_type& vertex) const {
        static_assert(std::negation_v<std::is_void<value_type>>, "To use this function, value_type can not be void.");
        return vertices_.at(vertex).val; 
    }


    template<typename V = value_type>
    void setVertexValue(const key_type& vertex, typename graph_traits::enable_if_not_void_t<V, V> newValue) {
        vertices_.at(vertex).val = newValue;
    }


private:

    vertices_map vertices_;
};



// #include <algorithm>


// template <typename Key, typename Value>
// inline UndirectedGraph<Key, Value>::size_type UndirectedGraph<Key, Value>::size() const noexcept
// { return vertices_.size(); }


// template <typename Key, typename Value>
// bool UndirectedGraph<Key, Value>::insertVertex(const key_type &newVertex)
// {
//     static_assert(std::is_trivially_constructible_v<value_type> || std::is_void_v<value_type>, "To use this function, value_type has to be trivially constructible.");
//     return vertices_.try_emplace(newVertex).second; 
// }

// // template <typename Key, typename Value>
// // bool UndirectedGraph<Key, Value>::insertVertex(const key_type &newVertex, value_type value)
// // {
// //     static_assert(!std::is_void_v<value_type>, "Cannot insert a vertex with a value when value_type is void.");
// //     return vertices_.insert({newVertex, {value}}).second;
// // }


// template <typename Key, typename Value>
// template <typename... Args>
// inline bool UndirectedGraph<Key, Value>::emplaceVertex(const key_type &newVertex, Args &&...args)
// {
//     static_assert(!std::is_void_v<value_type>, "Cannot insert a vertex with a value when value_type is void.");
//     return vertices_.try_emplace(newVertex, std::forward<Args>(args)...).second;
// }


// template <typename Key, typename Value>
// void UndirectedGraph<Key, Value>::removeVertex(const key_type &vertex)
// {
//     std::ranges::for_each(vertices_, 
//         [&vertex](auto& ref) { std::erase(ref.second.edges, vertex); });
//     vertices_.erase(vertex);
// }


// template <typename Key, typename Value>
// void UndirectedGraph<Key, Value>::addEdge(const key_type &a, const key_type &b)
// {
//     // if constexpr (std::is_pointer<edge_type>) {
//     //     auto a_ptr = vertices_.find(a);
//     // }
//     // else {
//     //     vertices_.at(a).edges.emplace_back(b);
//     //     vertices_.at(b).edges.emplace_back(a);
//     // }
//     vertices_.at(a).edges.emplace_back(b);
//     vertices_.at(b).edges.emplace_back(a);
// }


// template <typename Key, typename Value>
// void UndirectedGraph<Key, Value>::removeEdge(const key_type &a, const key_type &b)
// {
//     std::erase(vertices_.at(a).edges, b);
//     std::erase(vertices_.at(b).edges, a);
// }


// template <typename Key, typename Value>
// bool UndirectedGraph<Key, Value>::adjacent(const key_type &a, const key_type &b) const
// { return std::ranges::contains(vertices_.at(a).edges, b); }


// template <typename Key, typename Value>
// const UndirectedGraph<Key, Value>::edge_list &UndirectedGraph<Key, Value>::adjacent(const key_type &vertex) const
// { return vertices_.at(vertex).edges; }


// template <typename Key, typename Value>
// UndirectedGraph<Key, Value>::value_type UndirectedGraph<Key, Value>::getVertexValue(const key_type &vertex) const
// {
//     static_assert(std::negation_v<std::is_void<value_type>>, "To use this function, value_type can not be void.");
//     return vertices_.at(vertex).val; 
// }


// // template <typename Key, typename Value>
// // void UndirectedGraph<Key, Value>::setVertexValue(const key_type &vertex, value_type newValue)
// // {
// //     static_assert(std::negation_v<std::is_void<value_type>>, "To use this function, value_type can not be void.");
// //     return vertices_.at(vertex).val = newValue;
// // }
