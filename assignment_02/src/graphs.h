#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <fstream>
#include <limits>
#include "../../../CS509_2026AIM1004_2026AIM1007/assignment_01/src/csr.h"

const int INF = numeric_limits<int>::max();

bool bellmanFord(Csr& Csr, vector<int>& distances);
bool readFloydWarshall(string filePath, int& vertices, vector<vector<int>>& mat);
bool floydWarshall(vector<vector<int>>& dist, int numVertices);


#endif //GRAPHS_H