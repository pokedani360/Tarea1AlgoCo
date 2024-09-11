#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <bits/stdc++.h>
using namespace std;

template<typename Func>
void measureSortTime(Func sortFunc, vector<int> &data, const string &algorithmName);


void insertionSort(vector<int>& A);
void mergeSort(vector<int>& A, int p, int r);
void quickSort(vector<int>& A, int p, int r);
void cppSort(vector<int> &A);

vector<int> loadDataset(const string& filename);

#endif
