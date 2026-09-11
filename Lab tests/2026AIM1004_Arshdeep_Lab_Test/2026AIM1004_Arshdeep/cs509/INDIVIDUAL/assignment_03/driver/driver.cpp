#include <iostream>
#include <fstream>
#include <chrono>
#include "../../assignment_01/src/csr.h"
#include "../src/mst.h"

using namespace std;
using namespace std::chrono;

void printMst(MST& mst, int choice) {
    if (choice > 1) {
        cout << "Total MST weight: " << mst.mstWeight << "\n";
        return;
    }
    cout << "MST Edges" << "\n";
    for (edge entry: mst.mst) {
        cout << entry.second.first << " " << entry.second.second << " " << entry.first << "\n";
    }
    cout << "Total MST weight: " << mst.mstWeight << "\n";
}

int main() {
    cout << "Running MST algorithms" << "\n";
    
    int choice;
    cout << "Select Test Case:" << endl;
    cout << "1. mst_10.txt" << endl;
    cout << "2. mst_100.txt" << endl;
    cout << "3. mst_10000.txt" << endl;
    cout << "4. mst_50000.txt" << endl;
    cout << "5. mst_100000.txt" << endl;

    vector<string> testCases = {"10", "100", "10000", "50000", "100000"};
    cin >> choice;
    string file = "../tests/mst_";
    file += testCases[--choice] + ".txt";

    Csr csr;

    cout << "Algorithm: Kruskal's MST" << endl;

    csr.convert(file, true);
    auto start2 = high_resolution_clock::now();
    MST mstKruskal = kruskal(csr);
    auto end2 = high_resolution_clock::now();
    printMst(mstKruskal, choice);
    auto duration1 = duration_cast<milliseconds>(end2 - start2);
    cout << "Execution Time: " << duration1.count() << " ms" << endl;

    cout << "\nAlgorithm: Prim's MST" << endl;

    csr.convert(file, true);
    auto start1 = high_resolution_clock::now();
    MST mstPrim = prim(csr);
    auto end1 = high_resolution_clock::now();
    printMst(mstPrim, choice);
    auto duration2 = duration_cast<milliseconds>(end1 - start1);
    cout << "Execution Time: " << duration2.count() << " ms";

    string outFile = "../Outputs/output_mst" + testCases[choice] + ".txt";
    ofstream File(outFile);
    File << "Algorithm: Kruskal's MST" << endl;
    File << "MST Edges:" << endl;
    for (edge entry: mstKruskal.mst) {
        File << entry.second.first << " " << entry.second.second << " " << entry.first << "\n";
    }
    File << "Total MST weight: " << mstKruskal.mstWeight << endl;
    File << endl;
    File << "Algorithm: Prim's MST" << endl;
    File << "MST Edges:" << endl;
    for (edge entry: mstPrim.mst) {
        File << entry.second.first << " " << entry.second.second << " " << entry.first << "\n";
    }
    File << "Total MST weight: " << mstPrim.mstWeight << endl;


    return 0;
}