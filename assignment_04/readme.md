## Assignment 04: Vertex Coloring and Page Rank

### Objective
Implement structural graph algorithms on CSR-formatted graphs for individual assignment tasks:
1. **Greedy Vertex Coloring:** Assign colors to vertices using the Welsh-Powell heuristic such that no two adjacent vertices share the same color.
2. **PageRank:** Compute vertex centralities and ranks on a directed graph using an iterative power iteration approach.

---

### Algorithm / Approach
1. **Greedy Vertex Coloring (Welsh-Powell Ordering):**
    * Graph (Vertex) Coloring assigns a color to every vertex of an undirected graph such that no two adjacent vertices share the same color, while using as few colors as possible. Finding the true minimum number of colors (the chromatic number) is NP-hard, so this assignment uses a greedy heuristic that produces a valid, though not necessarily minimum, coloring.
    * Welsh-Powell Algorithm:
        * Computes the degree of every vertex directly from the CSR representation (`row_ptr`).
        * Sorts/orders the vertices by non-increasing degree to minimize the number of colors required.
        * Iterates through vertices in this order, greedily assigning each vertex the smallest available color index not currently used by any of its already-colored neighbors.
        * Repeat until done.

2. **PageRank Algorithm:**
    * PageRank estimates the relative importance of each vertex in a directed graph based on the structure of incoming links, originally developed to rank web pages. A vertex's rank is high if it is linked to by many vertices, or by vertices that themselves have high rank.
        * PR(v) = (1 - d) / N + d * sum over u -> v of ( PR(u) / outdegree(u) )
    * N is the total number of vertices and d is the damping factor (typically 0.85).
    * All vertices are initialized with rank 1/N.
    * A vertex with outdegree 0 (a dangling vertex) must not cause a divide-by-zero; distribute its rank contribution evenly across all vertices, or treat it as linking to all vertices.
    * Iterate the update for all vertices simultaneously (using the previous iteration's values) until the total change (e.g., sum of absolute differences) is less than or equal to the tolerance, or the maximum number of iterations is reached.
    * The sum of all PageRank values should remain approximately 1.0 after each iteration.

---

### Input Format
Text files in the following space-separated formats:

#### For Unweighted Undirected Adjacency-List (Vertex Coloring)
```text
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree neighbor1 neighbor2 ...
```
* **V:** Number of vertices.
* **E:** Number of undirected edges (each undirected edge is listed in both endpoints' adjacency lists but counted once in $E$).
* **u:** Vertex ID.
* **degree:** Number of neighbors for vertex $u$.

#### For Unweighted Directed Adjacency-List (PageRank)
```text
V E
u0 outdegree neighbor1 neighbor2 ...
u1 outdegree neighbor1 neighbor2 ...
...
u(V-1) outdegree neighbor1 neighbor2 ...
DAMPING d
TOLERANCE epsilon
MAX_ITERATIONS n
```
* **V:** Number of vertices.
* **E:** Number of directed outgoing edges.
* **u:** Vertex ID.
* **outdegree:** Number of outgoing neighbors for vertex $u$.
* **DAMPING / TOLERANCE / MAX_ITERATIONS:** Convergence criteria and parameters.

---

### Helper Functions / CSR Conversion
Pre-processes adjacency lists into Compressed Sparse Row (CSR) arrays (`row_ptr`, `col_idx`) before timer invocation. The CSR conversion function from Assignment 01 is reused as a mandatory preprocessing step and is excluded from timing. Timing strictly measures algorithm execution only.

---

### File Structure
* `csr.h` / `csr.cpp`: Adjacency list to unweighted CSR conversion routines.
* `vertexColor.cpp`: Welsh-Powell Greedy Vertex Coloring logic and validity checker.
* `pageRank.cpp`: Iterative PageRank power method implementation with dangling node handling.
* `vertexPR.h`: Header file for both alogirthms.
* `driver.cpp`: Main executable driver handling input validation, parameter parsing, CSR initialization, timing invocation, and standard output printing.

---

### Test Cases and Result Tables

#### 1. Vertex Coloring Results

| File | Vertices ($V$) | Edges ($E$) | Colors Used | Valid? | Execution Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `color_10.txt` | 10 | 37 | 5 | Yes | 0 ms | PASSED |
| `color_100.txt` | 100 | 590 | 7 | Yes | 0 ms | PASSED |
| `color_1000.txt` | 1,000 | 5906 | 7 | Yes | 2 ms | PASSED |
| `color_10000.txt` | 10,000 | 599,333 | 8 | Yes | 8 ms | PASSED |
| `color_50000.txt` | 50,000 | 300,369 | 8 | Yes | 106 ms | PASSED |

---

#### 2. PageRank Results

| File | Vertices ($V$) | Edges ($E$) | Damping | Top Vertex | Sum of Ranks | Iterations / Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `pagerank_10.txt` | 10 | 80 | 0.85 | Vertex 0 | 1.0 | 6 iter / 0 ms | PASSED |
| `pagerank_100.txt` | 100 | 800 | 0.85 | Vertex 0 | 1.0 | 6 iter / 0 ms | PASSED |
| `pagerank_1000.txt` | 1,000 | 8,000 | 0.85 | Vertex 0 | 1.00001 | 8 iter / 2 ms | PASSED |
| `pagerank_10000.txt` | 10,000 | 80,000 | 0.85 | Vertex 0 | 1.0007 | 9 iter / 13 ms | PASSED |
| `pagerank_50000.txt` | 50,000 | 400,000 | 0.85 | Vertex 0 | 0.999595 | 9 iter / 69 ms | PASSED |

---

### Complexity
* **Greedy Vertex Coloring (Welsh-Powell):** 
  * Time Complexity: $\\mathcal{O}(V \\log V + V + E)$ (Degree computation, vertex sorting, neighbor color scanning).
  * Auxiliary Space: $\\mathcal{O}(V)$ for color vector and degree permutation indices.

* **PageRank Algorithm:** 
  * Time Complexity: $\\mathcal{O}(I \\cdot (V + E))$ where $I$ is the number of iterations until convergence.
  * Auxiliary Space: $\\mathcal{O}(V)$ to store primary and previous iteration rank vectors.

