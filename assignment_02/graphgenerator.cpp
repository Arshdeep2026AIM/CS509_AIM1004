#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <set>

using namespace std;

// Generates unweighted undirected graphs (used for Triangle Counting & Betweenness Centrality)
void generateUnweighted(int V, string algoPrefix, string testId) {
    vector<set<int>> adj(V);
    int E = 0;

    // Connect vertices to maintain a base connected component
    for (int i = 1; i < V; i++) {
        int u = i;
        int v = rand() % i;
        if (adj[u].find(v) == adj[u].end()) {
            adj[u].insert(v);
            adj[v].insert(u);
            E++;
        }
    }

    // Add extra random edges for density (keeping E ≈ 2V to 4V)
    int maxExtra = 2 * V;
    for (int e = 0; e < maxExtra; e++) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && adj[u].find(v) == adj[u].end()) {
            adj[u].insert(v);
            adj[v].insert(u);
            E++;
        }
    }

    string testPath = "tests/" + algoPrefix + "_" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        tFile << i << " " << adj[i].size();
        for (int neighbor : adj[i]) {
            tFile << " " << neighbor;
        }
        tFile << "\n";
    }
    tFile.close();
    cout << "Generated: " << testPath << " (V=" << V << ", E=" << E << ")\n";
}

// Generates weighted directed graphs with possible negative weights (Bellman-Ford)
void generateWeightedDirected(int V, string testId) {
    vector<vector<pair<int, int>>> adj(V);
    int E = 0;
    int source = 0;

    // Ensure reachable path from source
    for (int i = 1; i < V; i++) {
        int u = rand() % i;
        int v = i;
        int w = (rand() % 30) - 5; // Allow small negative weights without creating negative cycles easily
        adj[u].push_back({v, w});
        E++;
    }

    // Extra directed edges
    int extraEdges = 2 * V;
    for (int e = 0; e < extraEdges; e++) {
        int u = rand() % V;
        int v = rand() % V;
        int w = (rand() % 30) - 5;
        if (u != v) {
            adj[u].push_back({v, w});
            E++;
        }
    }

    string testPath = "tests/bf_" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        tFile << i << " " << adj[i].size();
        for (auto edge : adj[i]) {
            tFile << " " << edge.first << " " << edge.second;
        }
        tFile << "\n";
    }
    tFile << "SOURCE " << source << "\n";
    tFile.close();
    cout << "Generated: " << testPath << " (V=" << V << ", E=" << E << ")\n";
}

// Generates dense matrix files for Floyd-Warshall (Adjacency Matrix format)
void generateFloydWarshallMatrix(int V, string testId) {
    string testPath = "tests/fw_" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << V << "\n";

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                tFile << 0;
            } else {
                int prob = rand() % 100;
                if (prob < 40) { // 40% chance of edge
                    int w = (rand() % 30) - 5;
                    tFile << w;
                } else {
                    tFile << "INF";
                }
            }
            if (j < V - 1) tFile << " ";
        }
        tFile << "\n";
    }
    tFile.close();
    cout << "Generated: " << testPath << " (Matrix V=" << V << ")\n";
}

// Generates unweighted undirected graphs with disconnected components and isolated nodes
void generateComponentUnweighted(int V, string testId) {
    vector<set<int>> adj(V);
    int E = 0;

    // Create 3 to 5 isolated components
    int numComponents = 3 + rand() % 3;
    int blockSize = V / numComponents;

    for (int c = 0; c < numComponents; c++) {
        int start = c * blockSize;
        int end = (c == numComponents - 1) ? V : start + blockSize;

        // Leave some components entirely isolated if size allows
        if (end - start <= 1) continue;

        for (int i = start + 1; i < end; i++) {
            int u = i;
            int v = start + (rand() % (i - start));
            if (adj[u].find(v) == adj[u].end()) {
                adj[u].insert(v);
                adj[v].insert(u);
                E++;
            }
        }
    }

    string testPath = "tests/cc_" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        tFile << i << " " << adj[i].size();
        for (int neighbor : adj[i]) {
            tFile << " " << neighbor;
        }
        tFile << "\n";
    }
    tFile.close();
    cout << "Generated: " << testPath << " (Connected Components V=" << V << ", E=" << E << ")\n";
}

int main() {
    srand(42);
    cout << "=========================================\n";
    cout << " Generating Assignment 2 Test Cases...\n";
    cout << "=========================================\n\n";

    // 1. Bellman-Ford Inputs (10, 100, 10000, 50000, 100000)
    vector<string> bfSizes = {"10", "100", "10000", "50000", "100000"};
    for (const auto& size : bfSizes) {
        generateWeightedDirected(stoi(size), size);
    }

    // 2. Floyd-Warshall Inputs (10, 100, 500, 1000, 2000)
    vector<string> fwSizes = {"10", "100", "500", "1000", "2000"};
    for (const auto& size : fwSizes) {
        generateFloydWarshallMatrix(stoi(size), size);
    }

    // 3. Triangle Counting Inputs (10, 100, 10000, 50000, 100000)
    vector<string> tcSizes = {"10", "100", "10000", "50000", "100000"};
    for (const auto& size : tcSizes) {
        generateUnweighted(stoi(size), "tc", size);
    }

    // 4. Betweenness Centrality Inputs (10, 100, 1000, 5000, 10000)
    vector<string> bcSizes = {"10", "100", "1000", "5000", "10000"};
    for (const auto& size : bcSizes) {
        generateUnweighted(stoi(size), "bc", size);
    }

    // 5. Connected Components Inputs (10, 100, 10000, 50000, 100000)
    vector<string> ccSizes = {"10", "100", "10000", "50000", "100000"};
    for (const auto& size : ccSizes) {
        generateComponentUnweighted(stoi(size), size);
    }

    cout << "\nAll test case files created successfully in 'tests/' directory!\n";
    return 0;
}