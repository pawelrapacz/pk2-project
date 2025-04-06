#include "CityGraph.h"

#include <algorithm>

// citymap::CityGraph::CityGraph()
// {
// }

// citymap::CityGraph::~CityGraph()
// {
// }

citymap::CityGraph::size_type citymap::CityGraph::size() const noexcept
{ return vertices_.size(); }


void citymap::CityGraph::addVertex(key_reference newVertex)
{ vertices_[newVertex]; }


void citymap::CityGraph::addVertex(key_reference newVertex, value_type value)
{ vertices_[newVertex] = {value}; }


void citymap::CityGraph::removeVertex(key_reference vertex)
{
    std::ranges::for_each(vertices_, [&vertex](auto& ref) { std::erase(ref.second.edges, vertex); });
    vertices_.erase(vertex);
}


void citymap::CityGraph::addEdge(key_reference a, key_reference b)
{
    vertices_.at(a).edges.emplace_back(b);
    vertices_.at(b).edges.emplace_back(a);
}


void citymap::CityGraph::removeEdge(key_reference a, key_reference b)
{
    std::erase(vertices_.at(a).edges, b);
    std::erase(vertices_.at(b).edges, a);
}


bool citymap::CityGraph::adjacent(key_reference a, key_reference b) const
{
    return std::ranges::contains(vertices_.at(a).edges, b);
}


const citymap::CityGraph::Edges& citymap::CityGraph::adjacent(key_reference vertex) const
{ return vertices_.at(vertex).edges; }


citymap::CityGraph::value_type citymap::CityGraph::getVertexValue(key_reference vertex) const
{ return vertices_.at(vertex).val; }


void citymap::CityGraph::setVertexValue(key_reference vertex, value_type newValue)
{ vertices_.at(vertex).val = newValue; }
