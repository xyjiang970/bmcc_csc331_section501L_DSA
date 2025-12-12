//***************************************************************
// Author: Xin Yu Jiang
// Due date: Dec. 12th, 2025
//
// method: genGenFromFile
// This method fills weights and edges in an existing graph
//   with values from a text file
//
//***************************************************************

// Note: graph_f25.h already contains:
// using namespace std;

#include <string>
void graphType::genFromFile(string fname)
{
    /*
    Initializing the adjacency matrix (note that the file only contains
    edges that DO exist).

    All other vertex pairs should have no connection (999)
    */
    for (int i = 0; i < gSize; i++)
    {
        for (int j = 0; j < gSize; j++)
        {
            // Set all edge weights to 999 (indicating no edge exists)
            weights[i][j] = 999; // genRandom.h already uses 999 as well
        }
        // Initialize the edges array (stores parent vertex in MST)
        edges[i] = 0;
        // Initialize the edgeWeights array (stores edge weights in MST)
        edgeWeights[i] = 0;
    }

    ifstream inFile(fname); // read input file

    // variables to store data
    string line; // read the first value (vertex or "end-of-file")
    int v1, v2;  // two vertices
    int weight;  // edge weight

    // Read edges from the file until end-of-file marker
    // The ">>" operator reads whitespace-separated values
    while (inFile >> line)
    {
        // end-of-file check
        if (line == "end-of-file" || line == "end of file" || line == "endoffile" || line == "\"end-of-file\"" || line == "\"end of file\"" || line == "\"endoffile\"")
        {
            break;
        }
        // Convert the first value from string to integer (first vertex)
        // We read it as a string first to check for "end-of-file"
        v1 = stoi(line);

        // second vertex and the edge weight
        inFile >> v2 >> weight;

        // Set the edge weight in the adjacency matrix
        // Since this is an UNDIRECTED graph, we must set both:
        // weights[v1][v2] - edge from v1 to v2
        // weights[v2][v1] - edge from v2 to v1 (same weight)
        weights[v1][v2] = weight;
        weights[v2][v1] = weight;
    }
    inFile.close();
}
