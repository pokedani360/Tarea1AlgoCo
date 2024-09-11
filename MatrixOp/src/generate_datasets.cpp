#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> generateRandomMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}

void saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    string folder = "data/";
    filesystem::create_directory(folder);

    ofstream file(folder + filename);
    if (!file) {
        cerr << "No se pudo abrir el archivo " << folder + filename << " para escritura." << endl;
        return;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    file << rows << " " << cols << endl;

    for (const auto& row : matrix) {
        for (int val : row) {
            file << val << " ";
        }
        file << endl;
    }

    file.close();
}

int main() {
    vector<pair<int, int>> dimensions = {
        {128, 128}, {256, 256}, {512, 512}, {1024, 1024}, // Matrices cuadradas
        {128, 256}, {256, 512}, {512, 1024}, {1024, 512}  // Matrices rectangulares
    };

    for (size_t i = 0; i < dimensions.size(); ++i) {
        int rowsA = dimensions[i].first;
        int colsA = dimensions[i].second;
        int rowsB = colsA;  
        int colsB = rowsA;  

        auto A = generateRandomMatrix(rowsA, colsA);
        auto B = generateRandomMatrix(rowsB, colsB);

        string filenameA = "matrix_A_" + to_string(rowsA) + "x" + to_string(colsA) + ".txt";
        string filenameB = "matrix_B_" + to_string(rowsB) + "x" + to_string(colsB) + ".txt";
        
        saveMatrixToFile(A, filenameA);
        saveMatrixToFile(B, filenameB);

        cout << "Matrices guardadas en: " << filenameA << " y " << filenameB << endl;
    }

    return 0;
}
