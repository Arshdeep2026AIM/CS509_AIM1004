#include <iostream>
#include <vector>
#include <cmath>
#include "../../assignment_01/src/csr.h"
#include "vertexPR.h"

using namespace std;

void pageRank(Csr& csr, vector<double>& pageR, int& iters, bool& converged) {
    int N = csr.csrGraph.numVertices;
    float damping = csr.damping;
    float tol = csr.tol;

    vector<int> outDegree(N);
    for(int i = 0; i < N; i++) {
        outDegree[i] = csr.csrGraph.rowPtr[i + 1] - csr.csrGraph.rowPtr[i];
    }

    pageR.assign(N, 1.0/N);
    while(iters < csr.maxIter && !converged) {
        vector<double> prev = pageR;

        float danglingSum = 0.0;
        for (int i = 0; i < N; i++) {
            if (outDegree[i] == 0) {
                danglingSum += prev[i];
            }
        }

        float evenContr = ((1 - damping) / N) + (damping * (danglingSum / N));
        fill(pageR.begin(), pageR.end(), evenContr);

        for (int u = 0; u < N; u++) {
            if (outDegree[u] == 0) continue;
            double contr = (damping * (prev[u] / outDegree[u]));
            for (int edge = csr.csrGraph.rowPtr[u]; edge < csr.csrGraph.rowPtr[u + 1]; edge++) {
                int neighbour = csr.csrGraph.colIdx[edge];
                pageR[neighbour] += contr;
            }
        }

        double diff = 0.0;
        for (int i = 0; i < N; i++) {
            diff += abs(pageR[i] - prev[i]);
        }
        if (diff < tol) converged = true;
        iters++;
    }
}