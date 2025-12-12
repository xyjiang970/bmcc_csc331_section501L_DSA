/******************************************************
Xin Yu (Jason) Jiang
CSC331 | Section: 501L
Program Assignment 5: Minimum Spanning Tree
Due Date: Dec. 12th, 2025 at 11:59PM

Program Name: csc331_501L_prog5_jiang.cpp

Program Purpose:
This program implements Prim's minimum spanning tree (MST) algorithm using C++.
It can either generate a random graph based on user input for the number of vertices,
or read graph data from a file specified via command line argument.
The program displays the graph, computes the MST, and outputs the edges and
total weight of the minimum spanning tree.

Programming environment used: VS-Code
******************************************************/

#include <iostream>
#include <fstream>
#include <string>

#include "graph_f25.h"
/*
Note the graph_f25.h file already includes the following files:
    - printGraph.h (Must complete method: printGraph)
    - genFromFile.h (Must complete method: genFromFile)
    - genRandom.h (DO NOT MODIFY - already completed)
So we do not need to include them again here in this main .cpp file.
They just need to be in the same directory!
*/

// find the number of vertices in the graph from file
int findGraphSize(std::string fname)
{
    std::ifstream inFile(fname);
    std::string line;
    int v1, v2, weight;
    int maxVertex = -1;

    while (inFile >> line)
    {
        // Check for end-of-file marker
        if (line == "end-of-file" || line == "end of file" || line == "endoffile" || line == "\"end-of-file\"" || line == "\"end of file\"" || line == "\"endoffile\"")
        {
            break;
        }

        // Parse vertices
        v1 = std::stoi(line);
        inFile >> v2 >> weight;

        // Track the maximum vertex number
        if (v1 > maxVertex)
            maxVertex = v1;
        if (v2 > maxVertex)
            maxVertex = v2;
    }

    inFile.close();

    // Number of vertices = max vertex index + 1 (since vertices start at 0)
    return maxVertex + 1;
}

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        // Command line argument provided - read from file
        std::string filename = argv[1];

        std::cout << "Filename: " << filename << std::endl;

        // Find the number of vertices in the graph
        int numVertices = findGraphSize(filename);
        std::cout << "Number of vertices: " << numVertices << std::endl;

        // Create graph instance with the determined size
        graphType myGraph(numVertices);

        // Load graph from file
        myGraph.genFromFile(filename);

        // Display the graph
        myGraph.printGraph();

        // Find minimum spanning tree starting from vertex 0
        myGraph.minimumSpanning(0);

        // Display the MST and its weight
        myGraph.printTreeAndWeight();

        // Destructor called automatically when myGraph goes out of scope
    }
    else
    {
        // No command line argument - prompt user for number of vertices
        int numVertices;
        std::cout << "enter number of vertices ... ";
        std::cin >> numVertices;

        // Create graph instance with user-specified size
        graphType myGraph(numVertices);

        // Generate random edges and weights
        myGraph.genRandom();

        // Display the graph
        myGraph.printGraph();

        // Find minimum spanning tree starting from vertex 0
        myGraph.minimumSpanning(0);

        // Display the MST and its weight
        myGraph.printTreeAndWeight();

        // Destructor called automatically when myGraph goes out of scope
    }

    /*
    Program will wait for the user to press a key before continuing,
    which will give you time to examine your program’s output before your
    operating system closes the console window.
    */
    // Only pause if NOT running with command line arguments
    if (argc == 1)
    {
        std::cin.clear(); // reset any error flags
        // ignore any characters in the input buffer until we find an enter character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Press Enter key to exit...";
        std::cin.get();
    }

    return 0;
}