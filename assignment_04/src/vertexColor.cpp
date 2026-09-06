#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "../../assignment_01/src/csr.h"
#include "vertexPR.h"

using namespace std;

int vertexColoring(Csr& csr, vector<int>& colors) {
    int totalColors = 0;
    int vert = csr.csrGraph.numVertices;
    if (vert == 0) {
        return totalColors;
    }

    vector<pair<int, int>> outDegree;
    for (int i = 0; i < vert; i++) {
        int degree = csr.csrGraph.rowPtr[i + 1] - csr.csrGraph.rowPtr[i];
        outDegree.push_back({degree, i});
    }

    sort(outDegree.begin(), outDegree.end(), [](pair<int, int>& a, pair<int, int>& b){
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    colors.assign(vert, -1);
    vector<bool> availableColors(vert, true);
    set<int> s = {};
    for (int i = 0; i < vert; i++) {
        int u = outDegree[i].second;

        for (int edge = csr.csrGraph.rowPtr[u]; edge < csr.csrGraph.rowPtr[u + 1]; edge++) {
            int neighbour = csr.csrGraph.colIdx[edge];
            if (colors[neighbour] != -1) availableColors[colors[neighbour]] = false;
        }

        for (int i = 0; i < vert; i++) {
            if (availableColors[i]) {
                colors[u] = i;
                break;
            }
        }

        for (int edge = csr.csrGraph.rowPtr[u]; edge < csr.csrGraph.rowPtr[u + 1]; edge++) {
            int neighbour = csr.csrGraph.colIdx[edge];
            if (colors[neighbour] != -1) availableColors[colors[neighbour]] = true;
        }

        if (s.find(colors[u]) == s.end()) {
            s.insert(colors[u]);
            totalColors++;
        }
    }
    return totalColors;
}