#ifndef GEMM_H
#define GEMM_H

#include <iostream>
#include <vector>
using namespace std;

void simpleMM(const vector<vector<int>>& mat11, const vector<vector<int>>& mat2);
void blockingMM(const vector<vector<int>>& mat11, const vector<vector<int>>& mat2);

void printMatrix(const vector<vector<int>>& mat, ostream& os);

#endif //GEMM_H