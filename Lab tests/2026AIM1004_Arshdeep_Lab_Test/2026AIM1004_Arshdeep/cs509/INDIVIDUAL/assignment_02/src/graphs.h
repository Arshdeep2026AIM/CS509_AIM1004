#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <fstream>
#include <limits>
#include "../../assignment_01/src/csr.h"

const int INF = 1e9;

bool bellmanFord(Csr& Csr, vector<int>& distances);
bool readFloydWarshall(string filePath, int& vertices, vector<vector<long long>>& mat);
bool readFloydWarshallCSR(string filePath, int& vertices, Csr& csr, vector<vector<long long>>& mat);
bool floydWarshall(vector<vector<long long>>& dist, int numVertices);
bool floydWarshallBlocking(vector<vector<long long>>& dist, int numVertices);


#endif //GRAPHS_H