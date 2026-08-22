#ifndef GEMM_H
#define GEMM_H

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> simpleMM(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2);
vector<vector<int>> blockingMM(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2);

void printMatrix(const vector<vector<int>>& mat, ostream& os);

#endif //GEMM_H