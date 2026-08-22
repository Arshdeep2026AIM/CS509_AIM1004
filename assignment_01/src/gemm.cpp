#include <iostream>
#include <vector>

#include "gemm.h"

using namespace std;

vector<vector<int>> simpleMM(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {

    int m = mat1.size(), k = mat2.size(), n = mat2[0].size();
    vector<vector<int>> mat;

    for (int i = 0; i < m; i++) {
        vector<int> row;
        for (int j = 0; j < n; j++) {
            int temp = 0;
            for (int c = 0; c < k; c++) {
                temp += (mat1[i][c] * mat2[c][j]);
            }
            row.push_back(temp);
        }
        mat.push_back(row);
    }
    return mat;
}

vector<vector<int>> blockingMM(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    
    int m = mat1.size(), k = mat2.size(), n = mat2[0].size(), B = 64;
    vector<vector<int>> mat(m, (vector<int>(n, 0)));

    for (int ii = 0; ii < m; ii += B) {
        for (int kk = 0; kk < k; kk += B) {
            for (int jj = 0; jj < n; jj += B) {
                
                for (int i = ii; i < min(m, ii+B); i++) {
                    for(int c = kk; c < min(k, kk+B); c++) {
                        int temp = mat1[i][c];
                        for (int j = jj; j < min(n, jj+B); j++) {
                            mat[i][j] += temp * mat2[c][j];
                        }
                    }
                }
            }
        }
    }
    return mat;
}

void printMatrix(const vector<vector<int>>& mat, ostream& os) {
    os << "Result matrix:\n";
    for (const auto& row : mat) {
        for (int entry : row) {
            os << entry << " ";
        }
        os << "\n";
    }
}