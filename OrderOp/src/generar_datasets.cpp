#include <bits/stdc++.h>
using namespace std;

vector<int> generarAleatorio(int n) {
    vector<int> datos(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, n);
    
    for (int i = 0; i < n; ++i) {
        datos[i] = distrib(gen);
    }
    return datos;
}

vector<int> generarOrdenadoAscendente(int n) {
    vector<int> datos(n);
    for (int i = 0; i < n; ++i) {
        datos[i] = i + 1;
    }
    return datos;
}

vector<int> generarParcialmenteOrdenado(int n, float porcentajeOrdenado) {
    vector<int> datos = generarOrdenadoAscendente(n);
    int limiteOrdenado = static_cast<int>(n * porcentajeOrdenado);
    
    random_device rd;
    mt19937 gen(rd());
    shuffle(datos.begin() + limiteOrdenado, datos.end(), gen);
    
    return datos;
}

vector<int> generarDuplicados(int n, float porcentajeDuplicados) {
    vector<int> datos;
    int limiteDuplicado = static_cast<int>(n * porcentajeDuplicados);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, limiteDuplicado);
    
    for (int i = 0; i < n; ++i) {
        datos.push_back(distrib(gen));
    }
    return datos;
}

void guardarDataset(const vector<int>& datos, const string& filename) {
    ofstream file(filename);
    for (const auto& num : datos) {
        file << num << "\n";
    }
    file.close();
}

void generarDatos(const string& basePath, int tamanoPequeno, int tamanoMedio, int tamanoGrande, 
                  function<vector<int>(int)> generador) {
    guardarDataset(generador(tamanoPequeno), basePath + "_pequeno.txt");
    guardarDataset(generador(tamanoMedio), basePath + "_medio.txt");
    guardarDataset(generador(tamanoGrande), basePath + "_grande.txt");
}

int main() {
    int tamanoPequeno = 100;
    int tamanoMedio = 10000;
    int tamanoGrande = 100000;

    int tipo;
    cout << "Selecciona el tipo de datos a generar:" << endl;
    cout << "1: Aleatorios" << endl;
    cout << "2: Ordenados" << endl;
    cout << "3: Parcialmente Ordenados" << endl;
    cout << "4: Duplicados" << endl;
    cout << "5: Casi Ordenados" << endl;
    cout << "Opción: ";
    cin >> tipo;

    switch (tipo) {
        case 1:
            generarDatos("data/aleatorio", tamanoPequeno, tamanoMedio, tamanoGrande, generarAleatorio);
            break;
        case 2:
            generarDatos("data/ordenado_ascendente", tamanoPequeno, tamanoMedio, tamanoGrande, generarOrdenadoAscendente);
            break;
        case 3:
            generarDatos("data/parcialmente_ordenado", tamanoPequeno, tamanoMedio, tamanoGrande, 
                         [](int n) { return generarParcialmenteOrdenado(n, 0.40); });
            break;
        case 4:
            generarDatos("data/duplicados", tamanoPequeno, tamanoMedio, tamanoGrande, 
                         [](int n) { return generarDuplicados(n, 0.50); });
            break;
        case 5:
            generarDatos("data/casi_ordenado", tamanoPequeno, tamanoMedio, tamanoGrande, 
                         [](int n) { return generarParcialmenteOrdenado(n, 0.80); });
            break;
        default:
            cout << "Tipo de datos no válido." << endl;
            return 1;
    }

    cout << "Datasets generados con éxito." << endl;
    return 0;
}
