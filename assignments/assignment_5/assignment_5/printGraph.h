//***************************************************************
// Author: Xin Yu Jiang
// Due date: Dec. 12th, 2025
//
// method: printGraph
// Display the values in the graph on the console in a row/column
// format
//
//***************************************************************

// Note: graph_f25.h already contains:
// using namespace std;

void graphType::printGraph()
{
    // header label for the graph output
    cout << "\nGraph:" << endl;

    // Outer loop: iterate through each row (each source vertex)
    // gSize is a private member variable (see graph_f25.h file)
    for (int i = 0; i < gSize; i++)
    {
        // Inner loop: iterate through each column (each destination vertex)
        for (int j = 0; j < gSize; j++)
        {
            // Print the weight value at position [i][j] in the adjacency matrix
            // This represents the edge weight from vertex i to vertex j
            // A value of 999 means there is no direct edge between the vertices
            cout << weights[i][j];

            // Print a tab character between columns for alignment
            // but not after the last column in each row
            if (j < gSize - 1)
                cout << "\t";
        }
        // move to the next line after printing all columns in current row
        cout << endl;
    }
    // blank line after  graph for formatting
    cout << endl;
}
