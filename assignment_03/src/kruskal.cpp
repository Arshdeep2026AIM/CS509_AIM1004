#include <iostream>
#include <vector>
#include <algorithm>
#include "../../assignment_01/src/csr.h"

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int i) {
        int root = i;
        while (parent[i] != root) {
            root = parent[i];
        }
        return root;
    }

    bool uni(int i, int j) {
        int rootI = find(i), rootJ = find(j);
        if (rootI == rootJ) return false;
        if (rank[rootI] < rank[rootJ]) parent[rootI] = rootJ;
        else if (rank[rootI] >= rank[rootJ]) parent[rootJ] = rootI;
        if (rank[rootI] == rank[rootJ]) rank[rootI]++;
        return true;
    }

};

void kruskal(Csr& csr) {
    DSU dsu(csr.csrGraph.numVertices);
    using edge = pair<int, pair<int, int>>;
    vector<edge> mstEdges;

    vector<edge> sortedEdges;
    int size = 0;
    for (int i = 0; i < csr.csrGraph.numVertices; i++) {
        int start = csr.csrGraph.rowPtr[i];
        int end = csr.csrGraph.rowPtr[i + 1];
        for (int j = start; j < end; j++) {
            if (i < csr.csrGraph.colIdx[j]) {
                sortedEdges.push_back({csr.csrGraph.values[j], {i, csr.csrGraph.colIdx[j]}});
                size++;
            }
        }
    }
    sort(sortedEdges.begin(), sortedEdges.end());

    int totalWeight = 0, idx = 0;
    while ((int)mstEdges.size() < csr.csrGraph.numVertices - 1) {
        edge e = sortedEdges[idx];

        int weight = e.first;
        int u = e.second.first;
        int v = e.second.second;

        if (dsu.uni(u, v)) {
            mstEdges.push_back(e);
            totalWeight += weight;
        }

        idx++;
    }

    for (edge row: mstEdges) {
        cout << "Weight: " << row.first << " " << "Edge: {" << row.second.first << ", " << row.second.second << "}" << "\n";
    }
    cout << "\n" << totalWeight;
}


int main() {

    Csr csr;
    csr.convert("test.txt", true);

    kruskal(csr);

    return 0;
}