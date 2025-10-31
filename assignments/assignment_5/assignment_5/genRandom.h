//***************************************************************
// Author: BMCC CSC331 Data Structures
//
// method: genRandom
// This method generates random weights and edges in an existing graph
//
//***************************************************************
#include <cfloat>
#include <cmath>
#include <string>
using namespace std;
void graphType::genRandom() {
  srand(time(0));
  const int wgtMax = 17;
  bool used[wgtMax];
  for (int i = 0; i < wgtMax; i++)
    used[i] = 0;
  for (int i = 0; i < gSize; i++){
    for (int j = i; j < gSize; j++)
      if (i == j)
        weights[i][j] = 999;
      else {
        int newWgt = rand()%wgtMax; // fill with unduplicated random values
	if (rand()%3 < 1)           // extra zeroes
	  newWgt = 0;
	while (used[newWgt])
          newWgt = rand()%wgtMax;
	if (newWgt == 0)
	  newWgt = 999;
	else
	  used[newWgt] = 1;
        weights[i][j] = newWgt;
        weights[j][i] = weights[i][j]; // undirected graph
      }
    edges[i] = 0;
    edgeWeights[i] = 0;
  }
}
