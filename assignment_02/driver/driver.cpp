#include <iostream>
#include <vector>
#include <fstream>
#include "../src/graphs.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    int choice = 0;
    cout << "Enter choice for algorithm:" << "\n";
    cout << "1. Bellman Ford" << "\n";
    cout << "2. Floyd Warshall" << "\n" << "->";
    cin >> choice;

    int size = -1;
    string file;
    if (choice == 1) {
        vector<string> graphSize = {"0", "10", "100", "10000", "50000", "100000"};
        cout << "Enter choice for graph size:" << "\n";
        cout << "1. 10" << "\n";
        cout << "2. 100" << "\n";
        cout << "3. 10000" << "\n";
        cout << "4. 50000" << "\n";
        cout << "5. 100000" << "\n" << "->";
        cin >> size;
        file = "bf_" + graphSize[size] + ".txt";
    }
    else if (choice == 2) {
        vector<string> matrixSize = {"0", "10", "100", "500", "1000"};
        cout << "Enter choice for matrix size:" << "\n";
        cout << "1. 10" << "\n";
        cout << "2. 100" << "\n";
        cout << "3. 500" << "\n";
        cout << "4. 1000" << "\n" << "->";
        cin >> size;
        file = "fw_" + matrixSize[size] + ".txt";
    }

    bool neg;
    if (choice == 1) {
        Csr csr;
        csr.convert("../tests/" + file, true);
        vector<int> dist;
        auto start = high_resolution_clock::now();
        neg = bellmanFord(csr, dist);
        auto end = high_resolution_clock::now();
        cout << neg << "\n";
        ofstream File("output_" + file);

        if (!neg) {
        int idx = 0;
            for (int entry: dist) {
                File << idx << "\t" << entry << "\n";
                idx++;
            }
        }
        else File << "Negative Cycle detected\n";
        File.close();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << duration.count() << " ms" <<"\n";

    }
    else if (choice == 2) {
        int vertices;
        vector<vector<long long>> adjMat;
        auto start = high_resolution_clock::now();
        readFloydWarshall("../tests/" + file, vertices, adjMat);
        neg = floydWarshall(adjMat, vertices);
        auto end = high_resolution_clock::now();
        cout << neg << "\n";
        auto duration = duration_cast<milliseconds>(end - start);
        cout << duration.count() << " ms" <<"\n";
        ofstream File("output_" + file);
        if (!neg) {
            for (auto& row : adjMat) {
                for (long long entry: row) {
                    File << entry << " ";
                }
                File << "\n";
            }
        }
        else File << "Negative Cycle detected\n";
    }


    return 0;
}