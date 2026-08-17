#include <iostream>
#include <vector>
#include <queue>
#include "../../assignment_01/src/csr.h"
#include "mst.h"

using namespace std;

MST prim(Csr& csr) {
    vector<bool> inMst(csr.csrGraph.numVertices, false);
    vector<edge> mstEdges;
    priority_queue<edge, vector<edge>, greater<edge>> pq; 

    inMst[0] = true;

    for (int i = csr.csrGraph.rowPtr[0]; i < csr.csrGraph.rowPtr[1]; i++) {
        pq.push({csr.csrGraph.values[i], {0, csr.csrGraph.colIdx[i]}});
    }

    int totalWeight = 0;
    while (!pq.empty() && (int)mstEdges.size() < csr.csrGraph.numVertices - 1) {
        edge top = pq.top();
        pq.pop();

        int weight = top.first;
        int u = top.second.first;
        int v = top.second.second;

        if (inMst[v]) continue;

        inMst[v] = true;
        for (int i = csr.csrGraph.rowPtr[v]; i < csr.csrGraph.rowPtr[v + 1]; i++) {
            pq.push({csr.csrGraph.values[i], {v, csr.csrGraph.colIdx[i]}});
        }

        mstEdges.push_back(top);
        totalWeight += weight;
    }

    return {mstEdges, totalWeight};
}

MST kruskal(Csr& csr) {
    DSU dsu(csr.csrGraph.numVertices);
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
    while (idx < size && (int)mstEdges.size() < csr.csrGraph.numVertices - 1) {
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

    return {mstEdges, totalWeight};
}