#include <iostream>
#include <chrono>

#include "..\src\mat.h"
#include "..\src\gemm.h"

using namespace std;
using namespace std::chrono;

int main() {
    string file;
    cout << "Choose a test input file to run: " << "\n";
    cout << "1. gemm_test_01.txt" << "\n";
    cout << "2. gemm_test_02.txt" << "\n";
    cout << "3. gemm_test_03.txt" << "\n";
    cout << "4. gemm_test_04.txt" << "\n";
    cout << "5. gemm_test_05.txt" << "\n";
    cout << "6. gemm_test_06.txt" << "\n";
    cout << "7. gemm_test_07.txt" << "\n";
    cout << "8. exit" << "\n";
    getline(cin, file);
    if (file ==  "8") {
        return 0;
    }

    matLoad("..\\tests\\gemm_test_0" + file + ".txt");
    cout << "\n";

    cout << "Algorithm: GEMM Simple" << "\n";
    auto start = high_resolution_clock::now();
    simpleMM(matX, matY);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " ms" << "\n";

    cout << "\n";

    cout << "Algorithm: GEMM Blocking" << "\n";
    auto start1 = high_resolution_clock::now();
    blockingMM(matX, matY);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1);
    cout << "Execution time: " << duration1.count() << " ms" << "\n";

    cout << "\n";

    return 0;
}