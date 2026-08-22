# CS509 Individual Assignments Repo

## Repository Overview
This repository contains the implementation of Assignments for CS509 Lab Work in C++.

## Student Details
* **Student Name:** Arshdeep Singh
* **Entry Number:** 2026AIM1004
* **Assignment Type:** Individual

## Language and Environment
* **Programming Language:** C++
* **Compiler:** `g++` 
* **Timing Method:** `std::chrono::high_resolution_clock`

## Directory Structure
```text
CS509_<EntryNumber>/
|-- README.md
|-- common_wrapper/
|   `-- wrapper.cpp
|-- assignment_01/
|   |-- src/
|   |   |-- mat.h
|   |   |-- mat.cpp
|   |   |-- gemm.h
|   |   `-- gemm.cpp
|   |-- driver/
|   |   `-- driver.cpp
|   |-- tests/
|   |   |-- gemm_test_01.txt
|   |   `-- ...
|   `-- outputs/
|       |-- output_01.txt
|       |-- expected_01.txt
|       `-- ...
|-- assignment_02/
.
```

## Common Wrapper: Build and Usage
The root `wrapper.cpp` serves as the repo-level interface. It launches the dedicated driver for Assignment 1.

### Compilation
```bash
g++ -O2 common_wrapper/wrapper.cpp -o wrapper
```

### Execution
```bash
./wrapper
```

---

## Assignment 01: General Matrix Multiplication (GEMM)

### Objective
Implement and compare standard nested-loop GEMM (`Simple`) with cache-friendly tiled/blocked GEMM (`Blocking`).

### Algorithm / Approach
1. **GEMM Simple:** Standard 3-nested-loop matrix multiplication computing $C[i][j] = \sum A[i][k] \times B[k][j]$.
2. **GEMM Blocking:** Tile-based matrix multiplication using a block size ($B = 64$) to optimize cache spatial and temporal locality.

### Input Format
The matrix text file specifies $M$, $K$, and $N$ followed by elements of Matrix $A$ ($M \times K$) and Matrix $B$ ($K \times N$):
```text
M K N
<Row 0 A of>
...
<Row A M-1 of>
<Row 0 B of>
...
<Row B K-1 of>
```

### File Structure
* `mat.h` / `mat.cpp`: Matrix loading logic from file.
* `gemm.h` / `gemm.cpp`: `simpleMM` and `blockingMM` implementations.
* `driver.cpp`: Reads input files, triggers timed algorithm executions, writes output files, and verifies actual output against expected output.

### Compilation
```bash
g++ -O2 assignment_01_gemm/src/mat.cpp assignment_01_gemm/src/gemm.cpp assignment_01_gemm/driver/driver.cpp -o assignment_01_gemm/driver/driver
```

### Execution
Run the driver directly or through the common wrapper:
```bash
./assignment_01_gemm/driver/driver
```

### Test Cases and Result Table

| Mode | Test File | Input Type | Input Size / Dimensions | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Single | `gemm_test_01.txt` | Matrix input | $2 \times 3$ and $3 \times 2$ | Result matrix | Result matrix | 0 ms | 0 ms | 64 | PASSED |
| Single | `gemm_test_02.txt` | Matrix input | $5 \times 6$ and $6 \times 7$ | Result matrix | Result matrix | 0 ms | 0 ms | 64 | PASSED |
| Single | `gemm_test_03.txt` | Matrix input | $10 \times 12$ and $12 \times 11$ | Result matrix | Result matrix | 0 ms | 0 ms | 64 | PASSED |
| Single | `gemm_test_04.txt` | Matrix input | $50 \times 60$ and $60 \times 55$ | Result matrix | Result matrix | 3 ms | 3 ms | 64 | PASSED |
| Single | `gemm_test_05.txt` | Matrix input | $100 \times 120$ and $120 \times 110$ | Result matrix | Result matrix | 20 ms | 23 ms | 64 | PASSED |
| Single | `gemm_test_06.txt` | Matrix input | $200 \times 250$ and $250 \times 225$ | Result matrix | Result matrix | 179 ms | 192 ms | 64 | PASSED |
| Single | `gemm_test_07.txt` | Matrix input | $1000 \times 1250$ and $1250 \times 1100$ | Result matrix | Result matrix | 25843 ms | 25160 ms | 64 | PASSED |


### Complexity
* **GEMM Simple:** Time Complexity: $\mathcal{O}(M \cdot K \cdot N)$, Auxiliary Space: $\mathcal{O}(M \cdot N)$
* **GEMM Blocking:** Time Complexity: $\mathcal{O}(M \cdot K \cdot N)$, Auxiliary Space: $\mathcal{O}(M \cdot N)$


## Assignment 02: Shortest Path Algorithms (Bellman-Ford & Floyd-Warshall)

### Assignment Mode
Single (Individual)

### Objective
Implement single-source shortest path using Bellman-Ford (with CSR graph format) and all-pairs shortest path using Floyd-Warshall, including negative-weight cycle detection.

### Algorithm / Approach
1. **Bellman-Ford:** Operates on directed graphs converted to Compressed Sparse Row (CSR) format. Relaxes all edges $|V|-1$ times and performs an additional pass to check for negative-weight cycles.
2. **Floyd-Warshall:** Operates on dense $V \times V$ adjacency matrices using dynamic programming. Computes shortest path distances for all pairs and checks diagonal entries $dist[i][i] < 0$ for negative cycles.

### Input Format
* **Bellman-Ford:** Weighted Adjacency List specifying $V$ and $E$, neighbor-weight pairs per vertex, and terminating with `SOURCE s`.
* **Floyd-Warshall:** Adjacency matrix of size $V \times V$ with weight values or `INF` for absent edges ($0$ on diagonal).

### Helper Functions / CSR Conversion
Adjacency lists are converted to CSR arrays (`row_ptr`, `col_idx`, `values`) prior to timer start. The CSR conversion logic is reused from previous modules.

### File Structure
* `csr.h` / `csr.cpp`: Converts adjacency list representations to Compressed Sparse Row (CSR) format.
* `graphs.h` / `graphs.cpp`: CSR-based Bellman-Ford implementation and negative-cycle detection and Matrix-based Floyd-Warshall implementation.
* `driver.cpp`: dedicated driver module that validates input files, builds data structures, invokes algorithms inside timing blocks, and formats output.

### Compilation
```bash
g++ ../../assignment_01/src/csr.cpp ../src/graphs.cpp ../driver/driver.cpp -o ../driver/driver
```

### Execution
```bash
./assignment_02_shortest_path/driver/driver
```

### Test Cases and Result Table

| Algorithm | Test File | Vertices ($V$) | Edges ($E$) | Source | Negative Cycle | Expected Output | Actual Output | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Bellman-Ford | `bf_10.txt` | 10 | 27 | 0 | No | Distances | Distances | 0 ms | PASSED |
| Bellman-Ford | `bf_100.txt` | 100 | 295 | 0 | No | Distances | Distances | 0 ms | PASSED |
| Bellman-Ford | `bf_10000.txt` | 10000 | 250950 | 0 | No | Distances | Distances | 17 ms | PASSED |
| Bellman-Ford | `bf_50000.txt` | 50000 | 997909 | 0 | No | Distances | Distances | 67 ms | PASSED |
| Bellman-Ford | `bf_100000.txt` | 100000 | 1500765 | 0 | No | Distances | Distances | 107 ms | PASSED |
| Floyd-Warshall | `fw_10.txt` | 10 | | N/A | No | Distance Matrix | Distance Matrix | 0 ms | PASSED |
| Floyd-Warshall | `fw_100.txt` | 100 | | N/A | No | Distance Matrix | Distance Matrix | 60 ms | PASSED |
| Floyd-Warshall | `fw_500.txt` | 500 | | N/A | No | Distance Matrix | Distance Matrix | 6369 ms | PASSED |
| Floyd-Warshall | `fw_1000.txt` | 1000 | | N/A | No | Distance Matrix | Distance Matrix | 49603 ms | PASSED |

### Complexity
* **Bellman-Ford:** Time Complexity: $\mathcal{O}(V \cdot E)$, Auxiliary Space: $\mathcal{O}(V + E)$
* **Floyd-Warshall:** Time Complexity: $\mathcal{O}(V^3)$, Auxiliary Space: $\mathcal{O}(V^2)$

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