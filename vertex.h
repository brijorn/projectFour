#pragma once
#include <list>
#include <string>

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

    // Returns true if this vertex shares an edge with v
    bool isAdjacentTo(Vertex *v)
    {
        for (Edge *e : edgeList)
            if (e->getU() == v || e->getV() == v)
                return true;
        return false;
    }

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
private:
    Vertex *u;
    Vertex *v;

public:
    std::string label;
    Edge(std::string label, Vertex *u, Vertex *v) : label(label), u(u), v(v) {}

    // Returns the u endpoint of this edge
    Vertex *getU() const { return u; }

    // Returns the v endpoint of this edge
    Vertex *getV() const { return v; }

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
