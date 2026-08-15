#ifndef MST_H
#define MST_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../../assignment_01/src/csr.h"

using edge = pair<int, pair<int,int>>;

struct MST {
    vector<edge> mst;
    int mstWeight;

    MST(vector<edge>& tree, int w) : mst(tree), mstWeight(w) {};
};

struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool uni(int i, int j) {
        int rootI = find(i), rootJ = find(j);
        if (rootI == rootJ) return false;
        if (rank[rootI] < rank[rootJ]) parent[rootI] = rootJ;
        else parent[rootI] = rootJ;
        if (rank[rootI] == rank[rootJ]) rank[rootI]++;
        return true;
    }
};


#endif // MST_H