#pragma once
#include <string>
#include <list>
#include "vertex.h"
#include <fstream>
#include <sstream>

class Graph
{
private:
    // Store vertices in a list. Graph does not need a destructor since the list handles the lifetime.
    std::list<Vertex> verticesList;
    std::list<Edge> edgesList;

    // Find a vertex by it's label else return null
    Vertex *findVertex(const std::string &label)
    {
        for (Vertex &v : verticesList)
        {
            if (v.label == label)
                return &v;
        }
        return nullptr;
    }

    // Find an edge by it's label else return null
    Edge *findEdge(const std::string &label)
    {
        for (Edge &e : edgesList)
        {
            if (e.label == label)
                return &e;
        }
        return nullptr;
    }

public:
    // Transfer ownership of the vertices to the Graph class
    Graph(std::string filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        // Variable used for storing each line read from the file
        std::string line;
        // Read the first line of the file containing all vertices (tab-separated)
        std::getline(file, line);

        // Convert the stored line into a stream for usage with getline()
        std::stringstream ss(line);

        // The name/stored value of the vertex/edge
        std::string label;

        while (std::getline(ss, label, '\t'))
        {
            insertVertex(label);
        }

        // Read each remaining line as an edge (two vertex labels and an edge label, tab-separated)
        while (std::getline(file, line))
        {
            std::stringstream ss(line);

            std::string vertexULabel, vertexVLabel, label;

            std::getline(ss, vertexULabel, '\t');
            std::getline(ss, vertexVLabel, '\t');
            std::getline(ss, label, '\t');

            // Look up both vertices by label to get pointers into verticesList
            Vertex *u = findVertex(vertexULabel);
            Vertex *v = findVertex(vertexVLabel);

            if (!u || !v)
            {
                throw std::runtime_error("Vertex could not be found for line: " + line);
            }

            insertEdge(label, *u, *v);
        }
    }

    // Returns a reference list of all vertices stored in the graph. If there are no vertices the list is empty
    std::list<Vertex *> vertices()
    {
        // Return a reference to the values stored in the graph to avoid copying
        std::list<Vertex *> ptrs;

        // Iterate verticesList and add a reference to the stored vertices to the reference list
        for (Vertex &v : verticesList)
        {
            ptrs.push_back(&v);
        }

        return ptrs;
    }

    // Returns a reference list of all edges stored in the graph. If there are no edges the list is empty
    std::list<Edge *> edges()
    {
        // Return a reference to the values stored in the graph to avoid copying
        std::list<Edge *> ptrs;

        // Iterate edgesList and add a reference to the stored edges to the reference list
        for (Edge &e : edgesList)
        {
            ptrs.push_back(&e);
        }

        return ptrs;
    }

    // Inserts a new vertex with the given label into the graph
    void insertVertex(std::string label)
    {
        verticesList.push_back(Vertex(label));
    }

    // Removes a vertex and all of its incident edges from the graph. Returns false if the vertex does not exist
    bool removeVertex(std::string label)
    {
        Vertex *lookupVertex = findVertex(label);
        if (!lookupVertex)
            return false;

        // Remove all edges where this vertex is an endpoint
        edgesList.remove_if([lookupVertex](const Edge &e)
                            { return e.getU() == lookupVertex || e.getV() == lookupVertex; });

        // Remove the vertex
        verticesList.remove_if([lookupVertex](const Vertex &vert)
                               { return &vert == lookupVertex; });
        return true;
    }


    // Inserts a new edge between vertices u and v with the given label, and registers it on both vertices
    void insertEdge(std::string label, Vertex &u, Vertex &v)
    {
        edgesList.push_back(Edge(label, &u, &v));
        // Take the address of the inserted edge so both vertices point to the same object in the list
        Edge *e = &edgesList.back();
        u.addEdge(e);
        v.addEdge(e);
    }

    // Removes an edge by its label from the graph. Returns false if the edge does not exist
    bool removeEdge(std::string label)
    {
        Edge *lookupEdge = findEdge(label);
        if (!lookupEdge)
            return false;

        // Remove the edge from the edgeList of every vertex that references it
        for (Vertex &v: verticesList) {
            v.removeEdge(lookupEdge);
        }
        
        // Remove the edge by comparing its address to the looked up edge
        edgesList.remove_if([lookupEdge](const Edge &e)
                            { return &e == lookupEdge; });

        return true;
    }

};
