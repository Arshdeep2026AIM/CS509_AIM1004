#include <iostream>
#include <fstream>
#include "../../../CS509_2026AIM1004_2026AIM1007/assignment_01/src/csr.h"
#include "graphs.h"

using namespace std;

bool bellmanFord(Csr& csr, vector<int>& distances) {
    int vertices = csr.csrGraph.numVertices;
    distances.assign(vertices, inf);
    distances[csr.csrGraph.sourceVertex] = 0;

    for (int iter = 0; iter < vertices - 1; iter++) {
        bool updated = false;
        for (int vertice = 0; vertice < vertices; vertice++) {
            if (distances[vertice] == inf) continue;

            for (int i = csr.csrGraph.rowPtr[vertice]; i < csr.csrGraph.rowPtr[vertice + 1]; i++) {
                int neighbor = csr.csrGraph.colIdx[i];
                int weight = csr.csrGraph.values[i];
                
                if (distances[vertice] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[vertice] + weight;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    
    for (int vertice = 0; vertice < vertices; vertice++) {
        if (distances[vertice] == inf) continue;
        for (int i = csr.csrGraph.rowPtr[vertice]; i < csr.csrGraph.rowPtr[vertice + 1]; i++) {
            int neighbor = csr.csrGraph.colIdx[i];
            int weight = csr.csrGraph.values[i];
            
            if (distances[vertice] + weight < distances[neighbor]) {
                return true;
            }
        }
    }
    return false;
}

bool readFloydWarshall(string filePath, int& vertices, vector<vector<long long>>& mat) {
    ifstream file(filePath);
    if (!file.is_open()) return false;
    file >> vertices;

    for (int i = 0; i < vertices; i++) {
        vector<long long> row;
        for (int j = 0; j < vertices; j++) {
            string val;
            file >> val;
            (val == "INF") ? row.push_back(INF) : row.push_back(stoll(val));
        }
        mat.push_back(row);
    }

    file.close();
    return true;
}

bool floydWarshall(vector<vector<long long>>& dist, int numVertices) {
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for(int j = 0; j < numVertices; j++) {
                dist[i][j] = (dist[i][k] == INF || dist[k][j] == INF) ? dist[i][j] : min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int diagonal = 0; diagonal < numVertices; diagonal++) {
        if (dist[diagonal][diagonal] < 0) return true;
    }

    return false;
}