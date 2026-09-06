#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <numeric>
#include <algorithm>

struct Edge {
    int src;
    int dest;
};

// Generates a directed scale-free graph using Preferential Attachment
void generate_pagerank_graph(int num_vertices, int edges_per_node, const std::string& filename) {
    if (num_vertices <= 0) return;

    std::mt19937 rng(42); // Fixed seed for reproducible benchmarks
    std::vector<Edge> edges;
    
    // Node degree tracking for preferential attachment selection
    std::vector<int> in_degree_nodes;

    // 1. Initial clique / ring startup to ensure connectivity
    int initial_nodes = std::min(num_vertices, edges_per_node + 1);
    for (int i = 0; i < initial_nodes; ++i) {
        for (int j = 0; j < initial_nodes; ++j) {
            if (i != j) {
                edges.push_back({i, j});
                in_degree_nodes.push_back(j);
            }
        }
    }

    // 2. Preferential attachment loop for remaining vertices
    for (int u = initial_nodes; u < num_vertices; ++u) {
        std::vector<int> targets;
        int added = 0;

        while (added < edges_per_node && !in_degree_nodes.empty()) {
            std::uniform_int_distribution<int> dist(0, in_degree_nodes.size() - 1);
            int v = in_degree_nodes[dist(rng)];

            // Avoid self-loops and duplicate directed edges
            if (v != u && std::find(targets.begin(), targets.end(), v) == targets.end()) {
                targets.push_back(v);
                edges.push_back({u, v});
                added++;
            }
        }

        // Update in-degree distribution pool
        for (int v : targets) {
            in_degree_nodes.push_back(v);
        }
        // Add current node to pool to allow incoming links
        in_degree_nodes.push_back(u);
    }

    // 3. Group outgoing edges by source node
    std::vector<std::vector<int>> adj_list(num_vertices);
    for (const auto& edge : edges) {
        adj_list[edge.src].push_back(edge.dest);
    }

    // 4. Output to file matching assignment parser specification
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Header line: <num_vertices> <num_edges>
    outfile << num_vertices << " " << edges.size() << "\n";

    // Adjacency format: <node_id> <out_degree> <target_1> <target_2> ...
    for (int u = 0; u < num_vertices; ++u) {
        outfile << u << " " << adj_list[u].size();
        for (int v : adj_list[u]) {
            outfile << " " << v;
        }
        outfile << "\n";
    }
    outfile << "DAMPING 0.85\n";
    outfile << "TOLERANCE 0.00001\n";
    outfile << "MAX_ITERATIONS 1000";

    outfile.close();
    std::cout << "Generated PageRank graph: " << filename 
              << " (" << num_vertices << " vertices, " 
              << edges.size() << " edges)" << std::endl;
}

int main() {
    // Required benchmark graph sizes
    std::vector<int> sizes = {10, 100, 1000, 10000, 50000};
    int edges_per_new_node = 8; // Average out-degree factor

    for (int V : sizes) {
        std::string filename = "pagerank_" + std::to_string(V) + ".txt";
        generate_pagerank_graph(V, edges_per_new_node, filename);
    }

    return 0;
}