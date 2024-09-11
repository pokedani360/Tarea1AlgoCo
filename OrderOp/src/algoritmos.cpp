#include "/home/dano/ejercicios/OrderOp/include/algoritmos.h"
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

template<typename Func>
void measureSortTime(Func sortFunc, vector<int> &data, const string &algorithmName) {
    vector<int> copy = data;
    auto start = high_resolution_clock::now();
    sortFunc(copy);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << algorithmName << " took " << duration.count() << " milliseconds." << endl;
}

void insertionSort(vector<int>& A) {
    int n = A.size();
    for (int j = 1; j < n; j++) {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

void merge(vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
    }

    L[n1] = numeric_limits<int>::max();
    R[n2] = numeric_limits<int>::max();

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void mergeSort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int partition(vector<int>& A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void quickSort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

void cppSort(vector<int> &A) {
    sort(A.begin(), A.end());
}