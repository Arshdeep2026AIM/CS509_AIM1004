#include <iostream>
#include <string>
#include <vector>

using namespace std;

void runAlgorithm(string targetFile) {
    string cmdFile = "mingw32-make -C ..";
    int buildStatus = system(cmdFile.c_str());
    if (buildStatus != 0) return;

    cout << "\n\n\n\n\n\n";

    string runCMD = "cd ..\\" + targetFile + "\\driver && driver.exe";
    int runStatus = system(runCMD.c_str());
    if (runStatus != 0) cout << "Unable to execute the file";
}

int main() {

    cout << "MAIN WRAPPER" << endl;
    cout << "Choose from the following Assignments:" << endl;
    cout << "1. General Matrix Multiplication" << endl;
    cout << "2. Bellman Ford" << endl;
    cout << "3. Floyd Warshall" << endl;
    cout << "4. Kruskal and Prim MST" << endl;
    cout << "5. Vertex Coloring and PageRank" << endl;
    cout << "6. exit" << endl;

    int choice;
    cin >> choice;
    choice--;

    string algoFile = "assignment_";
    vector<string> algos = {"01", "02", "02", "03", "04"};
    switch(choice){
        case 0:
            algoFile += algos[choice];
            break;
        case 1:
            algoFile += algos[choice];
            break;
        case 2:
            algoFile += algos[choice];
            break;
        case 3:
            algoFile += algos[choice];            
            break;
        case 4:
        algoFile += algos[choice];
            break;
        case 5:
            return 0;
        default:
            cout << "Error: Picked an invalid option";
            return 0;
    }

    runAlgorithm(algoFile);

    return 0;
}