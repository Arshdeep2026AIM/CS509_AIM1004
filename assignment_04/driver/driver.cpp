#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include "../../assignment_01/src/csr.h"
#include "../src/vertexPR.h"

using namespace std;
using namespace std::chrono;

int main() {

    int algoChoice = -1;
    cout << "1. Vertex Coloring\n";
    cout << "2. Page Ranking\n";
    cin >> algoChoice;
    
    vector<string> testCases = {"10", "100", "1000", "10000", "50000"};
    int choice = -1;    
    cout << "Graph size for test case:\n";
    cout << "1. 10 vertices" << endl;
    cout << "2. 100 vertices" << endl;
    cout << "3. 1000 vertices" << endl;
    cout << "4. 10000 vertices" << endl;
    cout << "5. 50000 vertices" << endl;
    cin >> choice;
    if (choice > 5 && choice < 1) return 1;
    
    Csr csr;
    vector<double> pR;
    switch(algoChoice) {
        case 1: {
            string testFile = "../tests/coloring_" + testCases[--choice] + ".txt";
            csr.convert(testFile);
            vector<int> result;

            auto startV = high_resolution_clock::now();
            int numColors = vertexColoring(csr, result);
            auto endV = high_resolution_clock::now();
            auto durationV = duration_cast<milliseconds>(endV - startV);

            bool correctness = true;
            for (int u = 0; u < csr.csrGraph.numVertices; u++) {
                for (int edge = csr.csrGraph.rowPtr[u]; edge < csr.csrGraph.rowPtr[u + 1]; edge++) {
                    int neighbour = csr.csrGraph.colIdx[edge];
                    if (result[u] == result[neighbour]) correctness = false;
                }
            }

            string outFileName = "../outputs/output_coloring_" + testCases[choice] + ".txt";
            ofstream outFile(outFileName);
            outFile << "Algorithm: Greedy Vertex Coloring\n";
            outFile << "Vertex colors:\n";
            for (int i = 0; i < csr.csrGraph.numVertices; i++) {
                outFile << i << " " << result[i] << endl;
            }
            outFile << "Colors used: " << numColors << endl;
            if (correctness) outFile << "Correctness: Valid\n";
            else outFile << "Correctness: Invalid\n";
            outFile << "Execution time: " << durationV.count() << " ms"; 
            outFile.close();

            cout << "Algorithm: Greedy Vertex Coloring\n";
            if (correctness) cout << "Correctness: Valid\n";
            else cout << "Correctness: Invalid\n";
            cout << "Execution time: " << durationV.count() << " ms\n";
            break;
        }

        case 2: {
            string testFile = "../tests/pagerank_" + testCases[--choice] + ".txt";
            csr.convert(testFile);
            vector<double> pR;
            int iterations = 0;
            bool converged = false;
            auto startP = high_resolution_clock::now();
            pageRank(csr, pR, iterations, converged);
            auto endP = high_resolution_clock::now();
            auto durationP = duration_cast<milliseconds>(endP - startP);

            string outFileName = "../outputs/output_pagerank_" + testCases[choice] + ".txt";
            ofstream outFile(outFileName);
            outFile << "Algorithm: PageRank\n";
            outFile << "Damping: 0.85\n";
            outFile << "Vertex ranks:\n";
            int max = 0;
            float sum = 0;
            for (int i = 0; i < csr.csrGraph.numVertices; i++) {
                if (pR[i] > pR[max]) max = i;
                outFile << i << " " << pR[i] << endl;
                sum += pR[i];
            }
            outFile << "Sum of ranks: " << sum << endl;
            outFile << "Iterations: " << iterations << endl;
            if (converged) outFile << "Converged: True\n";
            else outFile << "Converged: False\n";
            outFile << "Execution time: " << durationP.count() << " ms";
            outFile.close(); 

            cout << "Algorithm: PageRank\n";
            cout << "Top Vertex: " << max << endl;
            cout << "Execution time: " << durationP.count() << " ms\n"; 
            break;
        }
    }
    return 0;
}