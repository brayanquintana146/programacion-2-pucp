#include "funciones.h"


void cargarNumeros(const char *nombArch, int *&numeros) {
    ifstream archivo(nombArch, ios::in);
    int datos_aux[30];
    int numero;
    int cantDatos=0;
    while (archivo>>numero) {
        datos_aux[cantDatos] = numero;
        cantDatos++;
    }
    numeros = new int[cantDatos+1];
    for (int i=0; i<cantDatos; i++) {
        numeros[i] = datos_aux[i];
    }
    numeros[cantDatos] = -1;
}


void cargarNumeros(const char *nombArch, int *&numeros, int &cantDatos) {
    ifstream archivo(nombArch, ios::in);
    int datos_aux[30];
    int numero;
    cantDatos=0;
    while (archivo>>numero) {
        datos_aux[cantDatos] = numero;
        cantDatos++;
    }
    numeros = new int[cantDatos+1];
    for (int i=0; i<cantDatos; i++) {
        numeros[i] = datos_aux[i];
    }
}