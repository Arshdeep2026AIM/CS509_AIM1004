## Assignment 03: Graph Algorithms (Minimum Spanning Tree - Kruskal & Prim)

### Objective
Implement structural graph algorithms on weighted, undirected graphs using Compressed Sparse Row (CSR) format:
1. Minimum Spanning Tree (MST) using **Kruskal's Algorithm** (with Disjoint Set Union / DSU).
2. Minimum Spanning Tree (MST) using **Prim's Algorithm** (with Min-Priority Queue).

### Algorithm / Approach
1. **Kruskal's Algorithm:**
   * Extracts edge list representation from the weighted undirected CSR format.
   * Sorts all graph edges in non-decreasing order of weight.
   * Iterates through sorted edges and uses Disjoint Set Union (DSU / Union-Find) with path compression to add edges that do not introduce cycles until $V - 1$ edges are selected.
2. **Prim's Algorithm:**
   * Initializes tree expansion from vertex 0 for deterministic reproducibility.
   * Maintains a min-priority queue storing light-edge connections from tree nodes to fringe vertices.
   * Continuously picks and inserts the lowest-weight boundary edge expanding the tree until all $V$ vertices are spanned.

### Input Format
Text files in the following format:

#### For Weighted Undirected Adjacency-List (MST)
```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
```
* **V:** Number of vertices.
* **E:** Number of undirected edges (each undirected edge is counted once in $E$ even though it appears in both adjacency lists).
* **u:** Vertex ID.
* **degree:** Number of neighbors for vertex $u$.

### Helper Functions / CSR Conversion
Pre-processes weighted adjacency lists into Compressed Sparse Row (CSR) arrays (`row_ptr`, `col_idx`, `values`) before timer invocation. Both Kruskal's and Prim's algorithms run on the same pre-built CSR graph to compare execution timing and total weights. Timing measures only algorithm execution.

### File Structure
* `csr.h` / `csr.cpp`: Adjacency list to CSR conversion and sorting routines.
* `mst.cpp` / `mst.h` : Kruskal's MST logic with DSU cycle detection and Prim's MST logic with Min-Priority Queue.
* `driver.cpp`: Dedicated driver module for input validation, CSR setup, separate/comparative timed execution calls, and result printing.

---

### Test Cases and Result Table

| Algorithm | Test File | Vertices ($V$) | Edges ($E$) | Expected Weight | Kruskal Weight | Prim Weight | Kruskal Time | Prim Time | Equal? | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| MST (Kruskal & Prim) | `mst_10.txt` | 10 | 15 | 384 | 384 | 384 | 0 ms | 0 ms | Yes | PASSED |
| MST (Kruskal & Prim) | `mst_100.txt` | 100 | 250 | 2450 | 2450 | 2450 | 0 ms | 0 ms | Yes | PASSED |
| MST (Kruskal & Prim) | `mst_10000.txt` | 10000 | 30000 | 203306 | 203306 | 203306 | 31 ms | 133 ms | Yes | PASSED |
| MST (Kruskal & Prim) | `mst_50000.txt` | 50000 | 150000 | 1011325 | 1011325 | 1011325 | 180 ms | 793 ms | Yes | PASSED |
| MST (Kruskal & Prim) | `mst_100000.txt` | 100000 | 200000 | 2893888 | 2893888 | 2893888 | 243 ms | 1123 ms | Yes | PASSED |

---

### Complexity
* **Kruskal's Algorithm:** Time Complexity: $\mathcal{O}(E \log E)$ or $\mathcal{O}(E \log V)$, Auxiliary Space: $\mathcal{O}(V + E)$
* **Prim's Algorithm:** Time Complexity: $\mathcal{O}(E \log V)$ using Min-Priority Queue, Auxiliary Space: $\mathcal{O}(V + E)$