#include "/home/dano/ejercicios/OrderOp/include/algoritmos.h"
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

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
void measureSortTime(Func sortFunc, vector<int> &data, const string &algorithmName) {
    vector<int> copy = data;
    auto start = high_resolution_clock::now();
    
    sortFunc(copy);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << algorithmName << " took " << duration.count() << " milliseconds." << endl;
}

void procesarDatos(const string &filePath) {
    vector<int> dataset = loadDataset(filePath);

    measureSortTime(insertionSort, dataset, "Insertion Sort");
    measureSortTime([](vector<int>& A) { mergeSort(A, 0, A.size() - 1); }, dataset, "Merge Sort");
    measureSortTime([](vector<int>& A) { quickSort(A, 0, A.size() - 1); }, dataset, "Quick Sort");
    measureSortTime(cppSort, dataset, "C++ Standard Sort");
}

void seleccionarDatos() {
    int tipo;
    cout << "Selecciona el tipo de datos a ordenar:" << endl;
    cout << "1: Aleatorios" << endl;
    cout << "2: Ordenados" << endl;
    cout << "3: Parcialmente Ordenados" << endl;
    cout << "4: Duplicados" << endl;
    cout << "5: Casi Ordenados" << endl;
    cout << "Ingresa 0 para terminar"  << endl;
    cout << "Opción: ";
    cin >> tipo;

    int tamano;
    cout << "Selecciona el tamaño de los datos:" << endl;
    cout << "1: Pequeño" << endl;
    cout << "2: Medio" << endl;
    cout << "3: Grande" << endl;
    cout << "4: Todos" << endl;
    cout << "Opción: ";
    cin >> tamano;

    string path;

    switch (tipo) {
        case 1:
            if (tamano == 1 || tamano == 4) path = "data/aleatorio_pequeno.txt";
            if (tamano == 2 || tamano == 4) path = "data/aleatorio_medio.txt";
            if (tamano == 3 || tamano == 4) path = "data/aleatorio_grande.txt";
            break;
        case 2:
            if (tamano == 1 || tamano == 4) path = "data/ordenado_ascendente_pequeno.txt";
            if (tamano == 2 || tamano == 4) path = "data/ordenado_ascendente_medio.txt";
            if (tamano == 3 || tamano == 4) path = "data/ordenado_ascendente_grande.txt";
            break;
        case 3:
            if (tamano == 1 || tamano == 4) path = "data/parcialmente_ordenado_pequeno.txt";
            if (tamano == 2 || tamano == 4) path = "data/parcialmente_ordenado_medio.txt";
            if (tamano == 3 || tamano == 4) path = "data/parcialmente_ordenado_grande.txt";
            break;
        case 4:
            if (tamano == 1 || tamano == 4) path = "data/duplicados_pequeno.txt";
            if (tamano == 2 || tamano == 4) path = "data/duplicados_medio.txt";
            if (tamano == 3 || tamano == 4) path = "data/duplicados_grande.txt";
            break;
        case 5:
            if (tamano == 1 || tamano == 4) path = "data/casi_ordenado_pequeno.txt";
            if (tamano == 2 || tamano == 4) path = "data/casi_ordenado_medio.txt";
            if (tamano == 3 || tamano == 4) path = "data/casi_ordenado_grande.txt";
            break;
        default:
            cout << "Tipo de datos no válido." << endl;
            return;
    }

    procesarDatos(path);
}

int main() {
    while (true) 
        seleccionarDatos();
    return 0;
}