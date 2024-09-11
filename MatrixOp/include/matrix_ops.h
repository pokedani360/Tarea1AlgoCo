#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> matrixMultiplyCubic(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> matrixMultiplyOptimized(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B);

vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B);

vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B);

vector<vector<int>> transpose(const vector<vector<int>>& A);

#endif