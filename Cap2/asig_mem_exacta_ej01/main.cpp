#include <iostream>
#include "funciones.h"

using namespace std;

int main() {
    int* numeros;
    int cantNums;

    cargarNumeros("numeros.csv", numeros, cantNums);

    for (int i = 0; i<cantNums; i++) {
        cout << numeros[i] << endl;
    }

    delete[] numeros;

    return 0;
}