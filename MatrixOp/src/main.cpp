#include "/home/dano/ejercicios/MatrixOp/include/matrix_ops.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> readMatrixFromFile(const string& filename) {
    string folder = "data/";
    ifstream file(folder + filename);
    if (!file) {
        throw runtime_error("No se pudo abrir el archivo " + folder + filename);
    }

    int rows, cols;
    file >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}

template <typename Func>
auto measureExecutionTime(Func func, const vector<vector<int>>& A, const vector<vector<int>>& B) {
    auto start = chrono::high_resolution_clock::now();
    auto result = func(A, B);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    return make_pair(result, duration.count());
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

template <typename Func>
void measureAndPrintTime(Func func, const string& name, const vector<vector<int>>& A, const vector<vector<int>>& B, ofstream& resultsFile) {
    auto [result, time] = measureExecutionTime(func, A, B);
    resultsFile << name << " took " << time << " seconds." << endl;
    cout << name << " took " << time << " seconds." << endl;
}

int main() {
    try {
        string folder = "data/";
        ofstream resultsFile("results.txt");
        if (!resultsFile) {
            throw runtime_error("No se pudo abrir el archivo results.txt para escritura.");
        }

        for (const auto& entry : filesystem::directory_iterator(folder)) {
            string filename = entry.path().filename().string();

            vector<vector<int>> A = readMatrixFromFile(filename);
            vector<vector<int>> B = readMatrixFromFile(filename);

            int rowsA = A.size();
            int colsA = A[0].size();
            int rowsB = B.size();
            int colsB = B[0].size();

            if (colsA != rowsB) {
                resultsFile << "Error: El número de columnas de A (" << colsA << ") debe ser igual al número de filas de B (" << rowsB << ")." << endl;
                cout << "Error: El número de columnas de A (" << colsA << ") debe ser igual al número de filas de B (" << rowsB << ")." << endl;
                resultsFile << endl;
                continue;
            }

            resultsFile << "Comparando métodos de multiplicación de matrices " << rowsA << "x" << colsA << ":" << endl;

            measureAndPrintTime(matrixMultiplyCubic, "Multiplicación cúbica tradicional", A, B, resultsFile);
            measureAndPrintTime(matrixMultiplyOptimized, "Multiplicación cúbica optimizada (con transposición)", A, B, resultsFile);

            if (rowsA == colsA && rowsB == colsB) {
                measureAndPrintTime(strassen, "Multiplicación usando Strassen", A, B, resultsFile);
            } else {
                resultsFile << "Multiplicación usando Strassen no aplicable para matrices no cuadradas." << endl;
                cout << "Multiplicación usando Strassen no aplicable para matrices no cuadradas." << endl;
            }

            resultsFile << endl;
        }

        resultsFile.close();
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}