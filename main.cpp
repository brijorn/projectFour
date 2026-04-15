#include <iostream>
#include <string>
#include "graph.h"

void printMenu()
{
    std::cout << "------------\n";
    std::cout << "What would you like to do?\n";
    std::cout << "------------\n";
    std::cout << "1. Find edges incident on a vertex\n";
    std::cout << "2. Find a path in the graph\n";
    std::cout << "3. Insert an edge\n";
    std::cout << "4. Erase a vertex\n";
}

int main()
{
    std::string filename;
    std::cout << "Enter the file name: ";
    std::getline(std::cin, filename);

    Graph g(filename);
    std::cout << "Graph succesfuly read.\n";

    std::string input;

    do {
        printMenu();
        std::getline(std::cin, input);

        // Option 1: Find edges incident on a vertex
        if (input == "1") {
        }
        // Option 2: Find a path in the graph
        else if (input == "2") {
        }
        // Option 3: Insert an edge
        else if (input == "3") {
        }
        // Option 4: Erase a vertex
        else if (input == "4") {
        }
        else {
            std::cout << "Invalid option. Please enter 1-4.\n";
        }

    } while (true);
}
