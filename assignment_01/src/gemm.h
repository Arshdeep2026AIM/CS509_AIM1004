#ifndef GEMM_H
#define GEMM_H

#include <iostream>
#include <vector>
using namespace std;

void simpleMM(vector<vector<int>>& mat11, vector<vector<int>>& mat2);
void blockingMM(vector<vector<int>>& mat11, vector<vector<int>>& mat2);

#endif //GEMM_H