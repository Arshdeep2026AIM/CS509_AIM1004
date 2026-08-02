#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

template <size_t Rows, size_t Cols>
int checki_ng(int (&arr)[Rows][Cols], int idx1, int idx3) {
    for (int row = 0; row < idx1; row++) {
        for (int col = 0; col < idx3; col++) {
            cout << arr[row][col] << " ";
        }
        cout << "\n";
    }
}

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
                cout << "ERROR\n";
                return 1;
            }
        }
    }

    for (int row = 0; row < idx2; row++) {
        for (int col = 0; col < idx3; col++) {
            if (!(File >> z[row][col])) {
                cout << "ERROR\n";
                return 1;
            }
        }
    }

    int x[idx1][idx3];

    for (int row = 0; row < idx1; row++) {
        for (int col = 0; col < idx3; col++) {
            x[row][col] = 0;
        }
    }

    const int B = 2;
    for (int ii = 0; ii < idx1; ii+=B) {
        for (int jj = 0; jj < idx3; jj+=B) {
            for (int kk = 0; kk < idx2; kk+=B) {
                
                int i_max = min(idx1, ii + B);
                int j_max = min(idx3, jj + B);
                int k_max = min(idx2, kk + B);

                for (int i = ii; i < i_max; i++) {
                    for (int k = kk; k < k_max; k++) {
                        int temp = y[i][k];
                        for (int j = jj; j < j_max; j++) {
                            x[i][j] += temp * z[k][j];
                        }
                    }
                }
                checki_ng(x, idx1, idx3);
            }
        }
    }

    for (int row = 0; row < idx1; row++) {
        for (int col = 0; col < idx3; col++) {
            cout << x[row][col] << " ";
        }
        cout << "\n";
    }

    return 0;
}