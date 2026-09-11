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