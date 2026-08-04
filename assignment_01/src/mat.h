#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

extern vector<vector<int>> matX;
extern vector<vector<int>> matY;
void matLoad(string filePath);

#endif //MAT_H