#include "/home/dano/ejercicios/MatrixOp/include/matrix_ops.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> matrixMultiplyCubic(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    if (n != B.size()) {
        throw invalid_argument("El número de columnas de A debe ser igual al número de filas de B.");
    }

    vector<vector<int>> C(m, vector<int>(p, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

vector<vector<int>> matrixMultiplyOptimized(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    if (n != B.size()) {
        throw invalid_argument("El número de columnas de A debe ser igual al número de filas de B.");
    }

    vector<vector<int>> C(m, vector<int>(p, 0));

    vector<vector<int>> B_T = transpose(B);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B_T[j][k];
            }
        }
    }

    return C;
}

vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int m = n / 2;
    vector<vector<int>> A11(m, vector<int>(m)), A12(m, vector<int>(m)),
                                  A21(m, vector<int>(m)), A22(m, vector<int>(m)),
                                  B11(m, vector<int>(m)), B12(m, vector<int>(m)),
                                  B21(m, vector<int>(m)), B22(m, vector<int>(m));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    vector<vector<int>> S1 = subtract(B12, B22);
    vector<vector<int>> S2 = add(A11, A12);
    vector<vector<int>> S3 = add(A21, A22);
    vector<vector<int>> S4 = subtract(B21, B11);
    vector<vector<int>> S5 = add(A11, A22);
    vector<vector<int>> S6 = add(B11, B22);
    vector<vector<int>> S7 = subtract(A12, A22);
    vector<vector<int>> S8 = add(B21, B22);
    vector<vector<int>> S9 = subtract(A11, A21);
    vector<vector<int>> S10 = add(B11, B12);

    vector<vector<int>> P1 = strassen(A11, S1);
    vector<vector<int>> P2 = strassen(S2, B22);
    vector<vector<int>> P3 = strassen(S3, B11);
    vector<vector<int>> P4 = strassen(A22, S4);
    vector<vector<int>> P5 = strassen(S5, S6);
    vector<vector<int>> P6 = strassen(S7, S8);
    vector<vector<int>> P7 = strassen(S9, S10);

    vector<vector<int>> C11 = add(subtract(add(P5, P4), P2), P6);
    vector<vector<int>> C12 = add(P1, P2);
    vector<vector<int>> C21 = add(P3, P4);
    vector<vector<int>> C22 = subtract(add(P5, P1), add(P3, P7));

    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }

    return C;
}

vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

vector<vector<int>> transpose(const vector<vector<int>>& A) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> A_T(cols, vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A_T[j][i] = A[i][j];
        }
    }

    return A_T;
}
