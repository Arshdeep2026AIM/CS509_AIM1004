#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <fstream>
#include <limits>
#include "../../../CS509_2026AIM1004_2026AIM1007/assignment_01/src/csr.h"

const int INF = 1e9;

bool bellmanFord(Csr& Csr, vector<int>& distances);
bool readFloydWarshall(string filePath, int& vertices, vector<vector<long long>>& mat);
bool floydWarshall(vector<vector<long long>>& dist, int numVertices);


#endif //GRAPHS_H