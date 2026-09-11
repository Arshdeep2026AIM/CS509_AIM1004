#include <iostream>
#include <fstream>
#include <limits>
#include "../../assignment_01/src/csr.h"
#include "graphs.h"

using namespace std;

bool bellmanFord(Csr& csr, vector<int>& distances) {
    int vertices = csr.csrGraph.numVertices;
    distances.assign(vertices, INF);
    distances[csr.csrGraph.sourceVertex] = 0;

    for (int iter = 0; iter < vertices - 1; iter++) {
        bool updated = false;
        for (int vertice = 0; vertice < vertices; vertice++) {
            if (distances[vertice] == INF) continue;

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
        if (distances[vertice] == INF) continue;
        int neighbors = csr.csrGraph.rowPtr[vertice + 1] - csr.csrGraph.rowPtr[vertice];
        for (int i = csr.csrGraph.rowPtr[vertice]; i < csr.csrGraph.rowPtr[vertice] + neighbors; i++) {
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
            (val == "INF") ? row.push_back(INF) : row.push_back(stoi(val));
        }
        mat.push_back(row);
    }

    file.close();
    return true;
}

// Lab test 1
// Implementation of reading matrix from csr, New document mentions reading from a csr, it takes the resultnant matrix to fill as input only
bool readFloydWarshallCSR(string filePath, int& vertices, Csr& csr, vector<vector<long long>>& mat) {
    ifstream file(filePath);
    if (!file.is_open()) return false;

    for (int i = 0; i < csr.csrGraph.numVertices; i++) {
        vector<long long> row(csr.csrGraph.numVertices, INF);   //Initialises the vector not reachable as INF
        for (int j = csr.csrGraph.rowPtr[i]; j < csr.csrGraph.rowPtr[i + 1]; j++) {
            int neighbor = csr.csrGraph.colIdx[j];
            int weight = csr.csrGraph.values[j];
            row[neighbor] = weight;
        }
        mat.push_back(row);     // After updating the reachable vertices, updates the overall matrix
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

//Lab test 1
bool floydWarshallBlocking(vector<vector<long long>>& dist, int numVertices, int B) {

    // Implementation of blocking, using blocks on intermediate vertices as well
    for (int k = 0; k < min(numVertices, k+B); k+=B) {
        for (int ii = 0; ii < numVertices; ii+=B) {
            for (int jj = 0; jj < numVertices; jj+=B) {

                int rowEnd = min(ii+B, numVertices);        //This safeguards against condition where V(num of vertices) is not divisible by B
                int colEnd = min(jj+B, numVertices);
                int blockEnd = min(k+B, numVertices);

                for (int i = ii; i < rowEnd; i++) {
                    for (int c = k; c < blockEnd; c++) {
                        int temp = dist[i][c];
                        for (int j = jj; j < colEnd; j++) {
                            dist[i][j] = (temp == INF || dist[c][j] == INF) ? dist[i][j] : min(dist[i][j], temp + dist[c][j]);
                        }
                }
            }
        }
    }
}
    for (int diagonal = 0; diagonal < numVertices; diagonal++) {
        if (dist[diagonal][diagonal] < 0) return true;
    }

    return false;
}

int main() {
    vector<vector<long long>> mat;
    int vert;
    readFloydWarshall("../tests/fw_10.txt", vert, mat);

    floydWarshallBlocking(mat, vert, 24);
    //floydWarshall(mat, vert);

    for (auto row : mat) {
        for (long long entry : row) {
            cout << entry << " ";
        }
        cout << "\n";
    }

    return 0;
}