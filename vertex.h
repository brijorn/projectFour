#pragma once
#include <list>
#include <string>
#include <utility>
class Edge;

class Vertex
{
private:
    std::list<Edge *> edgeList;

public:
    std::string label;

    Vertex(std::string label) : label(label) {}

    std::string operator*()
    {
        return label;
    }

    // Returns a list of all edges incident on this vertex
    std::list<Edge *> incidentEdges()
    {
        std::list<Edge *> ptrs;

        for (Edge *e : edgeList)
        {
            ptrs.push_back(e);
        }

        return ptrs;
    }

    // Returns true if this vertex shares an edge with v (defined after Edge)
    bool isAdjacentTo(Vertex *v);

    // Registers an edge as incident on this vertex
    void addEdge(Edge *e)
    {
        edgeList.push_back(e);
    }

    // Removes an edge from this vertex's edge list by comparing pointers
    void removeEdge(Edge *e)
    {
        edgeList.remove_if([e](Edge *edge)
                           { return edge == e; });
    }
};

class Edge
{
public:
    std::string label;
    Vertex *u;
    Vertex *v;
    Edge(std::string label, Vertex *u, Vertex *v) : label(label), u(u), v(v) {}

    // Returns the label stored on this edge
    std::string operator*()
    {
        return label;
    }

    // Returns both endpoint vertices of this edge
    std::pair<Vertex*, Vertex*> endVertices() {
        return {u, v};
    }

    // Returns the endpoint that is not the given vertex, or nullptr if target is not an endpoint
    Vertex* opposite(Vertex *target) {
        if (u == target) return v;
        if (v == target) return u;
        return nullptr;
    }

    // Returns true if this edge shares an endpoint with edge e
    bool isAdjacentTo(Edge* e) {
        return e->u == u || e->u == v || e->v == u || e->v == v;
    }

    // Returns true if this edge is incident on the given vertex
    bool isIncidentOn(Vertex* target) {
        return target == u || target == v;
    }
};

// Defined after Edge so e->u and e->v are accessible
inline bool Vertex::isAdjacentTo(Vertex *v)
{
    for (Edge *e : edgeList)
        if (e->u == v || e->v == v)
            return true;
    return false;
}
