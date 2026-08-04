#include <iostream>
#include <fstream>
#include <vector>

#include "mat.h"

using namespace std;

vector<vector<int>> matX;
vector<vector<int>> matY;

void matLoad(string filePath) {
    matX.clear();
    matY.clear();

    ifstream File(filePath);
    int m, k, n;
    File >> m >> k >> n;

    for (int i = 0; i < m; i++) {
        vector<int> temp;
        for (int j = 0; j < k; j++) {
            int entry;
            File >> entry;
            temp.push_back(entry);
        }
        matX.push_back(temp);
    }

    for (int i = 0; i < k; i++) {
        vector<int> temp;
        for (int j = 0; j < n; j++) {
            int entry;
            File >> entry;
            temp.push_back(entry);
        }
        matY.push_back(temp);
    }
}
