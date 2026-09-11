#include <iostream>
#include <vector>
#include <fstream>
#include "csr.h"

using namespace std;

void Csr::convert(string path) {
    ifstream file(path);
    if (!file.is_open()) return;

    csrGraph.rowPtr.clear();
    csrGraph.colIdx.clear();
    csrGraph.values.clear();

    int index = 0;
    file >> csrGraph.numVertices >> csrGraph.numEdges;
    csrGraph.rowPtr.reserve(csrGraph.numVertices + 1);
    csrGraph.colIdx.reserve(2 * csrGraph.numEdges);
    csrGraph.values.reserve(2 * csrGraph.numEdges);

    for (int vertice = 0; vertice < csrGraph.numVertices; vertice++) {
        int v, degree;
        file >> v >> degree;
        csrGraph.rowPtr.push_back(index);

        for (int i = 0; i < degree; i++) {
            int neighbor;
            file >> neighbor;
            csrGraph.colIdx.push_back(neighbor);
            index++;
        }
    }
    csrGraph.rowPtr.push_back(index);

    string extra;
    if (file >> extra){
        file >> csrGraph.sourceVertex;
    }

    file.close();
}

void Csr::convert(string path, bool isWeighted) {
    ifstream file(path);
    if (!file.is_open()) return;

    csrGraph.rowPtr.clear();
    csrGraph.colIdx.clear();
    csrGraph.values.clear();

    int index = 0;
    file >> csrGraph.numVertices >> csrGraph.numEdges;
    csrGraph.rowPtr.reserve(csrGraph.numVertices + 1);
    csrGraph.colIdx.reserve(2 * csrGraph.numEdges);
    csrGraph.values.reserve(2 * csrGraph.numEdges);

    for (int vertice = 0; vertice < csrGraph.numVertices; vertice++) {
        int v, degree;
        file >> v >> degree;
        csrGraph.rowPtr.push_back(index);

        for (int i = 0; i < degree; i++) {
            int neighbor, weight;
            file >> neighbor;
            file >> weight;
            csrGraph.colIdx.push_back(neighbor);
            csrGraph.values.push_back(weight);
            index++;
        }
    }
    csrGraph.rowPtr.push_back(index);

    string extra;
    if (file >> extra){
        file >> csrGraph.sourceVertex;
    }

    file.close();
}

struct table {
    int vertice;
    vector<int> neighbors;
    vector<int> weight;
};

void Csr::convertEdge(string path) {
    ifstream file(path);
    if (!file.is_open()) return;

    csrGraph.rowPtr.clear();
    csrGraph.colIdx.clear();
    csrGraph.values.clear();

    vector<table> temp;

    char typeGraph;
    file >> typeGraph;
    int maxVertex = 0, numEdges = 0, flag = 0;   // Creating this temp structure as the input in text shows unsorted ordering of vertices as input
    if (typeGraph == 'D') {
        int u, v, w;
        file >> u;
        while (flag == 0) {
            if (u > maxVertex) maxVertex = u;
            
            struct table curr;
            curr.vertice = u;
            do {        // This loop will run until all the rows for the same vertice are processed
                file >> v >> w;
                curr.neighbors.push_back(v);
                curr.weight.push_back(w);
                numEdges++;
                if (!(file >> u)) flag = 1;  // This condition checks the EOF for input txt file
                if (flag == 1) break;
            } while(u == curr.vertice);
            temp.push_back(curr);
        }
    }
    else {  // For undirected, Incomplete for now, need to implement bidirectional edges, parallel and self edges.
        
    }

    csrGraph.numEdges = numEdges;
    csrGraph.numVertices = ++maxVertex;

    csrGraph.rowPtr.push_back(0);  // Here the CSR is created by first sorting the vertices accordingly
    int prevIdx = 0;
    for (int i = 0; i < maxVertex; i++) {
        int index = -1;
        vector<int> col, val;
        for (auto target : temp) { // Rather than sorting using a higher complexity method, can be optimized
            if (target.vertice == i) {
                col = target.neighbors;
                val = target.weight;
                index = csrGraph.rowPtr[prevIdx];
                prevIdx++;
                break;
            } 
        }
        if (index != -1) {
            for (int transfer = 0; transfer < col.size(); transfer++) {
                csrGraph.colIdx.push_back(col[transfer]);
                csrGraph.values.push_back(val[transfer]);
                index++;
            }
            csrGraph.rowPtr.push_back(index);
        }
        else {
            csrGraph.rowPtr.push_back(csrGraph.rowPtr.back());
            prevIdx++;
        }
    }
    csrGraph.rowPtr.push_back(csrGraph.rowPtr.size() + 1);

    file.close();
}
/*
int main() {
    Csr csr;
    csr.convertEdge("test.txt");

    cout << csr.csrGraph.numVertices << "  " << csr.csrGraph.numEdges << "\n";

    for (int entry : csr.csrGraph.rowPtr) {
        cout << entry << " ";
    }
    cout << "\n";
    for (int entry : csr.csrGraph.colIdx) {
        cout << entry << " ";
    }
    cout << "\n";
    for (int entry : csr.csrGraph.values) {
        cout << entry << " ";
    }
    cout << "\n";


    return 0;
}*/