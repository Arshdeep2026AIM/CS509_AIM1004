#include <iostream>
#include <string>
#include <chrono>

#include "..\src\csr.h"

using namespace std;
using namespace std::chrono;

int main() {
    Csr csr;
    csr.convertEdge("../src/test.txt");

    for (int entry : csr.csrGraph.rowPtr) {
        cout << entry << " ";
    }
    cout << "\n";
    for (int entry : csr.csrGraph.colIdx) {
        cout << entry << " ";
    }
    cout << "\n";
    for (int entry : csr.csrGraph.values) {
        cout << entry << " ";
    }
    cout << "\n";


    return 0;
}