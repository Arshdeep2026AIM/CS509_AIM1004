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
