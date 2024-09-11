# Tarea1AlgoCo

Este repositorio contiene dos carpetas principales:

- **MatrixOp**: Implementación de algoritmos de multiplicación de matrices.
- **OrderOp**: Implementación de algoritmos de ordenamiento.

Ambas carpetas contienen:

- Una carpeta `include` con los headers.
- Una carpeta `src` con los archivos `.cpp`.

## Compilación

Cada carpeta tiene su propio archivo `compilar.txt`. Para compilar en `OrderOp`, recuerda agregar `g++` al inicio de la primera línea. El código de compilación correcto es:

g++ -o main src/main.cpp src/algoritmos.cpp -Iinclude

## Datasets
Los datasets ya están creados y se encuentran en la carpeta data. Sin embargo, es posible recrearlos si se desea.

## Benchmarks
El archivo bench.cpp se utiliza para medir el tiempo de ejecución de todos los archivos .txt en la carpeta data.
El archivo main.cpp de OrderOp permite seleccionar datasets específicos para realizar pruebas.
El archivo main.cpp de MatrixOp mide el tiempo de ejecución de todos los archivos .txt de matrices.
Notas
Si al compilar encuentras problemas, revisa los #include para verificar que las rutas a los headers estén correctamente definidas.

Lo siento por quien tenga que revisar esta tarea, intenté ordenarlo lo mejor posible antes de q se acabara el tiempo.
