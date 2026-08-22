#include <iostream>
#include <string>
#include <chrono>

#include "..\src\mat.h"
#include "..\src\gemm.h"

using namespace std;
using namespace std::chrono;

int main() {
    string choice;
    cout << "Choose a test input file to run:\n";
    cout << "1. gemm_test_01.txt\n";
    cout << "2. gemm_test_02.txt\n";
    cout << "3. gemm_test_03.txt\n";
    cout << "4. gemm_test_04.txt\n";
    cout << "5. gemm_test_05.txt\n";
    cout << "6. gemm_test_06.txt\n";
    cout << "7. gemm_test_07.txt\n";
    cout << "8. exit\n";
    cout << "Enter choice: ";
    getline(cin, choice);

    if (choice == "8" || choice.empty()) {
        return 0;
    }

    string testNumber = "0" + choice;
    string testFilePath = "..\\tests\\gemm_test_" + testNumber + ".txt";

    matLoad(testFilePath);
    cout << "\n";

    ofstream file1("output_simple_" + testNumber + ".txt");
    ofstream file2("output_blocking_" + testNumber + ".txt");

    // --- GEMM Simple Execution Time ---
    cout << "Algorithm: GEMM Simple\n";
    auto start = high_resolution_clock::now();
    vector<vector<int>> result = simpleMM(matX, matY);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    printMatrix(result, file1);
    cout << "Execution time: " << duration.count() << " ms\n\n";

    // --- GEMM Blocking Execution Time ---
    cout << "Algorithm: GEMM Blocking\n";
    auto start1 = high_resolution_clock::now();
    vector<vector<int>> resultB = blockingMM(matX, matY);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1);
    printMatrix(resultB, file2);
    cout << "Execution time: " << duration1.count() << " ms\n\n";

    return 0;
}