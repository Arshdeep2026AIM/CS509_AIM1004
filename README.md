# CS509 Individual Assignments Repo

## Repository Overview
This repository contains the implementation of Assignment 1 for CS509 Lab Work, focusing on General Matrix Multiplication (GEMM) algorithms in C++.

## Student Details
* **Student Name:** Arshdeep Singh
* **Entry Number:** 2026AIM1004
* **Assignment Type:** Single (Individual)

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
* `bellman_ford.h` / `bellman_ford.cpp`: CSR-based Bellman-Ford implementation and negative-cycle detection.
* `floyd_warshall.h` / `floyd_warshall.cpp`: Matrix-based Floyd-Warshall implementation.
* `driver.cpp`: dedicated driver module that validates input files, builds data structures, invokes algorithms inside timing blocks, and formats output.

### Compilation
```bash
g++ -O2 assignment_02_shortest_path/src/csr.cpp assignment_02_shortest_path/src/bellman_ford.cpp assignment_02_shortest_path/src/floyd_warshall.cpp assignment_02_shortest_path/driver/driver.cpp -o assignment_02_shortest_path/driver/driver
```

### Execution
```bash
./assignment_02_shortest_path/driver/driver
```

### Test Cases and Result Table

| Algorithm | Test File | Vertices ($V$) | Edges ($E$) | Source | Negative Cycle | Expected Output | Actual Output | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Bellman-Ford | `bf_10.txt` | 10 | | 0 | No | Distances | Distances | | PASSED |
| Bellman-Ford | `bf_100.txt` | 100 | | 0 | No | Distances | Distances | | PASSED |
| Bellman-Ford | `bf_10000.txt` | 10000 | | 0 | No | Distances | Distances | | PASSED |
| Bellman-Ford | `bf_50000.txt` | 50000 | | 0 | No | Distances | Distances | | PASSED |
| Bellman-Ford | `bf_100000.txt` | 100000 | | 0 | No | Distances | Distances | | PASSED |
| Floyd-Warshall | `fw_10.txt` | 10 | | N/A | No | Distance Matrix | Distance Matrix | | PASSED |
| Floyd-Warshall | `fw_100.txt` | 100 | | N/A | No | Distance Matrix | Distance Matrix | | PASSED |
| Floyd-Warshall | `fw_500.txt` | 500 | | N/A | No | Distance Matrix | Distance Matrix | | PASSED |
| Floyd-Warshall | `fw_1000.txt` | 1000 | | N/A | No | Distance Matrix | Distance Matrix | | PASSED |
| Floyd-Warshall | `fw_2000.txt` | 2000 | | N/A | No | Distance Matrix | Distance Matrix | | PASSED |

### Complexity
* **Bellman-Ford:** Time Complexity: $\mathcal{O}(V \cdot E)$, Auxiliary Space: $\mathcal{O}(V + E)$
* **Floyd-Warshall:** Time Complexity: $\mathcal{O}(V^3)$, Auxiliary Space: $\mathcal{O}(V^2)$