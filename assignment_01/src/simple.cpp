#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

int main() {
    ifstream File("inp.txt");
    int idx1, idx2, idx3;

    if (!(File >> idx1 >> idx2 >> idx3)) {
        return 1;
    }

    int y[idx1][idx2], z[idx2][idx3];
    for (int row = 0; row < idx1; row++) {
        for (int col = 0; col < idx2; col++) {
            if (!(File >> y[row][col])) {
                cout << "ERROR";
                return 1;
            }
        }
    }

    for (int row = 0; row < idx2; row++) {
        for (int col = 0; col < idx3; col++) {
            if (!(File >> z[row][col])) {
                cout << "ERROR";
                return 1;
            }
        }
    }

    File.close();

    int x[idx1][idx3];

    auto start = high_resolution_clock::now();

    for (int i = 0; i < idx1; i++) {
        for (int j = 0; j < idx3; j++) {
            int temp = 0;
            for (int k = 0; k < idx2; k++) {
                temp = temp + (y[i][k] * z[k][j]);
            }
            x[i][j] = temp;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    for (int i = 0; i < idx1; i++) {
        for (int j = 0; j < idx3; j++) {
            cout << x[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "Extraction Time(microseconds): " << duration.count();

    return 0;
}