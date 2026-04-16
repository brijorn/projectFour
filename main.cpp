#include <iostream>
#include <string>
#include "graph.h"
using namespace std;
void printMenu()
{
    cout << "------------\n";
    cout << "What would you like to do?\n";
    cout << "------------\n";
    cout << "1. Find edges incident on a vertex\n";
    cout << "2. Find a path in the graph\n";
    cout << "3. Insert an edge\n";
    cout << "4. Erase a vertex\n";
}

int main()
{
    string filename;
    cout << "Enter the file name: ";
    getline(cin, filename);

    Graph g(filename);
    cout << "Graph succesfuly read.\n";

    string input;

    do {
        printMenu();
        // Use getline() vertex labels with spaces
        getline(cin, input);

        // Option 1: Find edges incident on a vertex
        if (input == "1") {
            cout << "Enter the label of the vertex: ";
            getline(cin, input);

            Vertex* v = g.findVertex(toLower(input));
            if (!v) {
                cout << "The vertex '" + input + "' could not be found in the graph.\n";
                continue;
            }

            for (Edge* e: v->incidentEdges()) {
                cout << v->label << " to " << e->opposite(v)->label << " is " << e->label << "\n";
            }
        }
        // Option 2: Find a path in the graph
        else if (input == "2") {
            cout << "Enter the label of the first vertex: ";
            getline(cin, input);

            // The starting vertex of the path
            Vertex* u = g.findVertex(toLower(input));
            if (!u) {
                cout << "The vertex '" + input + "' could not be found in the graph.\n";
                continue;
            }

            cout << "Enter the label of the second vertex: ";
            getline(cin, input);

            // The end vertex of the path
            Vertex* v = g.findVertex(toLower(input));
            if (!v) {
                cout << "The vertex '" + input + "' could not be found in the graph.\n";
                continue;
            }

            // DFS to find a path between the two vertices
            list<Vertex*> path = g.findPath(u, v, {});
            if (path.empty()) {
                cout << "Could not find a path between '" + u->label + "' and '" + v->label + "'\n";
                continue;
            }

            // Print path
            bool first = true;
            for (Vertex* pathVertex : path) {
                if (!first) cout << " to ";
                cout << pathVertex->label;
                first = false;
            }
            cout << "\n";
        }
        // Option 3: Insert an edge
        else if (input == "3") {
            cout << "Enter the label of the first vertex: ";
            getline(cin, input);

            // The first endpoint of the new edge
            Vertex* u = g.findVertex(toLower(input));
            if (!u) {
                cout << "The vertex '" + input + "' could not be found in the graph.\n";
                continue;
            }

            cout << "Enter the label of the second vertex: ";
            getline(cin, input);

            // The second endpoint of the new edge
            Vertex* v = g.findVertex(toLower(input));
            if (!v) {
                cout << "The vertex '" + input + "' could not be found in the graph.\n";
                continue;
            }

            cout << "Enter the edge label: ";
            getline(cin, input);

            // No duplicate edges allowed between the same two vertices
            if (u->isAdjacentTo(v)) {
                cout << "An edge between '" + u->label + "' and '" + v->label + "' already exists.\n";
                continue;
            }

            g.insertEdge(input, *u, *v);
            cout << "Edge inserted.\n";
        }
        // Option 4: Erase a vertex
        else if (input == "4") {
            cout << "Enter the label of the vertex to erase: ";
            getline(cin, input);

            // Remove the vertex and all of its incident edges
            if (!g.removeVertex(toLower(input))) {
                cout << "The vertex '" + input + "' could not be found in the graph.\n";
                continue;
            }

            cout << "Vertex removed.\n";
        }
        else {
            cout << "Invalid option. Please enter 1-4.\n";
        }

    } while (true);

    return 0;
}
