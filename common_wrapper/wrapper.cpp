#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void runGraphDriver() {
    cout << "\n--- Launching Graph Algorithms Driver ---\n";
    int status = system("./driver_graph");
    if (status != 0) {
        cout << "[!] Error: Driver failed to execute or executable missing ('./driver_graph').\n";
    }
}

void runMatrixDriver() {
    cout << "\n--- Launching GEMM Matrix Driver ---\n";
    cout << "Enter test case number/ID (default '01'): ";
    string testId;
    cin >> testId;
    
    string command = "./driver_matrix " + testId;
    int status = system(command.c_str());
    if (status != 0) {
        cout << "[!] Error: Driver failed to execute or executable missing ('./driver_matrix').\n";
    }
}

int main() {
    while (true) {
        cout << "\n=================================================\n";
        cout << "        CS509 Common Repository Wrapper          \n";
        cout << "=================================================\n";
        cout << "1. Run Assignment 1: Graph Algorithms (BFS, DFS, SSSP)\n";
        cout << "2. Run Assignment 1: Matrix Multiplication (GEMM)\n";
        cout << "3. Exit\n";
        cout << "Select option (1-3): ";

        int choice;
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1:
                runGraphDriver();
                break;
            case 2:
                runMatrixDriver();
                break;
            case 3:
                cout << "Exiting wrapper.\n";
                return 0;
            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }
    return 0;
}