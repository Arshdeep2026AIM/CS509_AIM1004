#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <set>
#include <string>
#include <cstdlib>

using namespace std;

struct Edge {
    int u, v, weight;
};

void generateMSTGraph(int V, int targetE, const string& filename, int minWeight = 1, int maxWeight = 100) {
    mt19937 rng(1337); // Fixed seed for reproducible test graphs
    uniform_int_distribution<int> weightDist(minWeight, maxWeight);

    // Track existing undirected edges to avoid duplicates and self-loops
    vector<set<int>> adjSet(V);
    vector<Edge> edges;

    // Step 1: Guarantee connectivity by building a Random Spanning Tree (V - 1 edges)
    vector<int> nodes(V);
    iota(nodes.begin(), nodes.end(), 0);
    shuffle(nodes.begin(), nodes.end(), rng);

    for (int i = 1; i < V; ++i) {
        int u = nodes[i];
        // Connect node[i] to a randomly selected already-connected node
        uniform_int_distribution<int> parentDist(0, i - 1);
        int v = nodes[parentDist(rng)];
        int w = weightDist(rng);

        if (u > v) swap(u, v);
        adjSet[u].insert(v);
        edges.push_back({u, v, w});
    }

    // Step 2: Add additional random edges to meet target E (~2V to 4V)
    uniform_int_distribution<int> nodeDist(0, V - 1);
    int currentE = V - 1;

    while (currentE < targetE) {
        int u = nodeDist(rng);
        int v = nodeDist(rng);

        if (u == v) continue;
        if (u > v) swap(u, v);

        // Check if edge already exists
        if (adjSet[u].find(v) == adjSet[u].end()) {
            adjSet[u].insert(v);
            int w = weightDist(rng);
            edges.push_back({u, v, w});
            currentE++;
        }
    }

    // Step 3: Build Adjacency List (each undirected edge in both endpoints)
    vector<vector<pair<int, int>>> adj(V);
    for (const auto& e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    // Sort neighbors by vertex ID for consistent formatting
    for (int u = 0; u < V; ++u) {
        sort(adj[u].begin(), adj[u].end());
    }

    // Step 4: Write output file according to Section 5.1 format
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error: Could not create output file " << filename << endl;
        return;
    }

    // Header line: V E
    outfile << V << " " << targetE << "\n";

    // Vertex lines: u degree neighbor1 weight1 neighbor2 weight2 ...
    for (int u = 0; u < V; ++u) {
        outfile << u << " " << adj[u].size();
        for (const auto& neighbor : adj[u]) {
            outfile << " " << neighbor.first << " " << neighbor.second;
        }
        outfile << "\n";
    }

    outfile.close();
    cout << "Generated " << filename << " (V=" << V << ", E=" << targetE << ")\n";
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        int V = atoi(argv[1]);
        int E = atoi(argv[2]);
        string filename = "mst_" + to_string(V) + ".txt";
        generateMSTGraph(V, E, filename);
        return 0;
    }

    cout << "Generating standard required MST test graphs...\n";

    // Required sizes from Section 4.2 table (sparse graphs with E approx 2V to 3V)
    generateMSTGraph(10, 15, "mst_10.txt");
    generateMSTGraph(100, 250, "mst_100.txt");
    generateMSTGraph(10000, 30000, "mst_10000.txt");
    generateMSTGraph(50000, 150000, "mst_50000.txt");
    
    // Large sparse graph for 100,000 vertices (E = 2 * V = 200,000 edges)
    generateMSTGraph(100000, 200000, "mst_100000.txt");

    return 0;
}