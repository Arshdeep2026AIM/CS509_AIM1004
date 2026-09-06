#ifndef VERTEXPR_H
#define VERTEXPR_H

#include <iostream>
#include "../../assignment_01/src/csr.h"
using namespace std;

int vertexColoring(Csr& csr, vector<int>& colors);
void pageRank(Csr& csr, vector<double>& pageR, int& iters, bool& converged);

#endif