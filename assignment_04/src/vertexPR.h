#ifndef VERTEXPR_H
#define VERTEXPR_H

#include <iostream>
#include "../../assignment_01/src/csr.h"
using namespace std;

int vertexColoring(Csr& csr, vector<int>& colors);
void PageRank(Csr& csr, vector<float> pageR);

#endif