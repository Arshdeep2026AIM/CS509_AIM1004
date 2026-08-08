#include <iostream>
#include <fstream>
#include <limits>
#include "../../../CS509_2026AIM1004_2026AIM1007/assignment_01/src/csr.h"
#include "graphs.h"

using namespace std;

bool bellmanFord(Csr& csr, vector<int>& distances) {
    int vertices = csr.csrGraph.numVertices;
    distances.assign(vertices, INF);
    distances[csr.csrGraph.sourceVertex] = 0;

    for (int iter = 0; iter < vertices - 1; iter++) {
        for (int vertice = 0; vertice < vertices; vertices++) {
            if (distances[vertice] == INF) continue;

            int neighbors = csr.csrGraph.rowPtr[vertice + 1] - csr.csrGraph.rowPtr[vertice];
            for (int i = csr.csrGraph.colIdx[vertice]; i < csr.csrGraph.colIdx[vertice] + neighbors; i++) {
                int neighbor = csr.csrGraph.colIdx[i];
                int weight = csr.csrGraph.values[i];
                
                if (distances[vertice] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[vertice] + weight;
                }
            }
        }
    }

    
    for (int vertice = 0; vertice < vertices; vertices++) {
        int neighbors = csr.csrGraph.rowPtr[vertice + 1] - csr.csrGraph.rowPtr[vertice];
        for (int i = csr.csrGraph.colIdx[vertice]; i < csr.csrGraph.colIdx[vertice] + neighbors; i++) {
            int neighbor = csr.csrGraph.colIdx[i];
            int weight = csr.csrGraph.values[i];
            
            if (distances[vertice] + weight < distances[neighbor]) {
                return true;
            }
        }
    }

    return false;
}

bool readFloydWarshall(string filePath, int& vertices, vector<vector<int>>& mat) {
    ifstream file(filePath);
    if (!file.is_open()) return false;
    file >> vertices;

    for (int i = 0; i < vertices; i++) {
        vector<int> row;
        for (int j = 0; j < vertices; j++) {
            string val;
            file >> val;
            (val == "INF") ? row.push_back(INF) : row.push_back(stoi(val));
        }
        mat.push_back(row);
    }

    file.close();
    return true;
}

bool floydWarshall(vector<vector<int>>& dist, int numVertices) {
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