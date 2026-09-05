#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include "../../assignment_01/src/csr.h"
#include "../src/vertexPR.h"

using namespace std;

int main() {

    int algoChoice = -1;
    cout << "1. Vertex Coloring\n";
    cout << "2. Page Ranking\n";
    cin >> algoChoice;
    algoChoice--;
    
    vector<string> testCases = {"10", "100", "1000", "10000", "50000"};
    int choice = -1;    
    cout << "Graph Size for test Case:\n";
    cout << "1. 10" << endl;
    cout << "2. 100" << endl;
    cout << "3. 1000" << endl;
    cout << "4. 10000" << endl;
    cout << "5. 50000" << endl;
    cin >> choice;
    choice--;

    return 0;
    
}