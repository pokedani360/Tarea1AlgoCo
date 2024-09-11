#include "/home/dano/ejercicios/OrderOp/include/algoritmos.h"
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;
namespace fs = filesystem;

vector<int> loadDataset(const string &filename) {
    ifstream file(filename);
    vector<int> data;
    int value;

    while (file >> value) {
        data.push_back(value);
    }

    file.close();
    return data;
}

template<typename Func>
void measureSortTime(Func sortFunc, vector<int> &data, const string &algorithmName, ofstream &resultFile) {
    vector<int> copy = data;
    auto start = high_resolution_clock::now();
    
    sortFunc(copy);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout << algorithmName << " took " << duration.count() << " milliseconds." << endl;
    resultFile << algorithmName << " took " << duration.count() << " milliseconds." << endl;
}


void procesarDatos(const string &filePath, ofstream &resultFile) {
    vector<int> dataset = loadDataset(filePath);

    cout << "\n--- Procesando archivo: " << filePath << " ---" << endl;
    resultFile << "\n--- Procesando archivo: " << filePath << " ---" << endl;

    measureSortTime(insertionSort, dataset, "Insertion Sort", resultFile);
    measureSortTime([](vector<int>& A) { mergeSort(A, 0, A.size() - 1); }, dataset, "Merge Sort", resultFile);
    measureSortTime([](vector<int>& A) { quickSort(A, 0, A.size() - 1); }, dataset, "Quick Sort", resultFile);
    measureSortTime(cppSort, dataset, "C++ Standard Sort", resultFile);
}



void ejecutarTodosLosArchivos(ofstream &resultFile) {
    string folderPath = "data/";

    for (const auto &entry : fs::directory_iterator(folderPath)) {
        string filePath = entry.path().string();
        if (filePath.substr(filePath.find_last_of(".") + 1) == "txt") {
            procesarDatos(filePath, resultFile);
        }
    }
}


int main() {
    ofstream resultFile("results.txt");
    
    ejecutarTodosLosArchivos(resultFile);
    
    resultFile.close();
    return 0;
}
