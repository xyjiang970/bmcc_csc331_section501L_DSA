//***************************************************************
// Author: D.S. Malik (page 706)
//
// class graphType
// This class specifies the operations to find a minimum spanning tree in a graph.
//***********Minimum Spanning Tree 
#include <cfloat>
#include <cmath>
#include <string>
using namespace std;
class graphType {
  public:
    void printGraph();
    void genFromFile(string fname);
    void genRandom();
    //Function to generate random weights and edges in an existing graph
    void minimumSpanning(int sVertex);
    //Function to create a minimum spanning tree with
    //root as sVertex.
    // Postcondition: A minimum spanning tree is created.
    // The weight of the edges is also saved in the array
    // edgeWeights.
    void printTreeAndWeight();
    //Function to output the edges of the minimum spanning tree
    //and the weight of the minimum spanning tree.
    //Postcondition: The edges of a minimum spanning tree
    // and their weights are printed.
    graphType(int size = 0);
    //Constructor
    //Postcondition: gSize = 0; maxSize = size;
    //The graph (undirected and weighted) is represented by the adjacency matrix named weights.
    // weights is a two-dimensional array to store the weights
    //   of the edges.
    // edges is an array to store the edges of a minimum
    //   spanning tree.
    // edgeWeights is an array to store the weights of the
    //   edges of a minimum spanning tree.
    ~graphType();
    //Destructor
    //The storage occupied by the vertices and the arrays
    //weights, edges, and edgeWeights is deallocated.
  private:
    int gSize,source;
    double **weights;
    int *edges;
    double *edgeWeights;
};
void graphType::minimumSpanning(int sVertex) {
  int startVertex, endVertex;
  double minWeight;
  source = sVertex;
  bool *mstv;
  mstv = new bool[gSize];
  for (int j = 0; j < gSize; j++)  {
    mstv[j] = false;
    edges[j] = source;
    edgeWeights[j] = weights[source][j];
  }
  mstv[source] = true;
  edgeWeights[source] = 0;
  for (int i = 0; i < gSize - 1; i++)  {
    minWeight = DBL_MAX;
    for (int j = 0; j < gSize; j++)
      if (mstv[j])
        for (int k = 0; k < gSize; k++)
          if (!mstv[k] && weights[j][k] < minWeight) {
            endVertex = k;
            startVertex = j;
            minWeight = weights[j][k];
          }
    mstv[endVertex] = true;
    edges[endVertex] = startVertex;
    edgeWeights[endVertex] = minWeight;
  } //end for
} //end minimumSpanning
void graphType::printTreeAndWeight() {
  double treeWeight = 0;
  cout << "Source Vertex: " << source << endl;
  cout << "Edges Weight" << endl;
  for (int j = 0; j < gSize; j++) {
    if (edges[j] != j) {
      treeWeight = treeWeight + edgeWeights[j];
      cout << "("<<edges[j] << ", " << j << ") " << edgeWeights[j] << endl;
    }
  }
  cout << endl;
  cout << "Minimum spanning Tree Weight: "  << treeWeight << endl;
} //end printTreeAndWeight
#include "printGraph.h"
#include "genFromFile.h"
#include "genRandom.h"
// The definitions of the constructor and the destructor are as follows:
graphType::graphType(int size) {
  gSize = size;
  weights = new double*[size];
  for (int i = 0; i < size; i++)
    weights[i] = new double[size];
  edges = new int[size];
  edgeWeights = new double[size];
}
//Destructor
graphType::~graphType() {
  for (int i = 0; i < gSize; i++)
    delete [] weights[i];
  delete [] weights;
  delete [] edges;
  delete [] edgeWeights;
  cout << "\nGraph deleted." << endl;
}

