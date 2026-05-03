#include "funciones.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

void cargarInventario(const char*nombArch, void*&inventario) {
    ifstream archivo(nombArch, ios::in);
    void **registros=nullptr;
    void *insumo;
    int num=0, capacidad=0;

    while (leerInventario(archivo, insumo)) {
        if (num==capacidad) {
            incrementarEspacio(registros, num, capacidad);
        }
        registros[num]=insumo;
        num++;
    }
    if (registros == nullptr) registros = new void* [1]{};
    else registros[num] = nullptr;

    inventario = registros;
}


bool leerInventario(ifstream&archivo, void*&insumo) {
    // I001,Café Arábica,50,kg
    char *codigo, *nombre, *unidadMedida;
    int cantidad;


    if (archivo.eof()) return false;
    codigo = leerCadenaDelim(archivo, ',');
    nombre = leerCadenaDelim(archivo, ',');
    archivo>>cantidad;
    archivo.get();
    unidadMedida=leerCadenaDelim(archivo, '\n');

    void **reg = new void* [5];
    reg[0] = codigo;
    reg[1] = nombre;
    reg[2] = new int {cantidad};
    reg[3] = new int{0};// cantidad requerida
    reg[4] = unidadMedida;

    insumo = reg;

    return true;
}

char *leerCadenaDelim(ifstream&archivo, char delim) {
    char aux[200], *ptrCadena;
    archivo.getline(aux, 200, delim);
    ptrCadena = new char[strlen(aux)+1];
    strcpy(ptrCadena, aux);
    return ptrCadena;
}

void incrementarEspacio(void**&registros, int num, int&capacidad) {
    capacidad+=5;

    if (registros == nullptr) registros = new void* [capacidad+1]{};
    else {
        void **aux = new void* [capacidad+1]{};
        for (int i=0; i<num; i++) {
            aux[i] = registros[i];
        }
        delete [] registros;
        registros = aux;
    }
}


void cargarMenu(const char*nombArch, void*&menu) {
    ifstream archivo(nombArch, ios::in);
    void **registros = nullptr;
    void *bebida;
    int num=0, capacidad=0;

    while (leerMenu(archivo, bebida)) {
        if (num==capacidad) {
            incrementarEspacio(registros, num, capacidad);
        }
        registros[num]=bebida;
        num++;
    }
    if (registros==nullptr) registros = new void*[1]{};
    else registros[num]=nullptr;

    menu = registros;
}

bool leerMenu(ifstream&archivo, void*&bebida) {
    // B001,Espresso Doble,Un espresso [...] fuerte,C,2.50,120
    char *codigo, *nombre, *descripcion, tipo;
    bool disponible=false;
    double precio;
    int cantVendidas;

    if (archivo.eof()) return false;
    codigo = leerCadenaDelim(archivo, ',');
    nombre = leerCadenaDelim(archivo, ',');
    descripcion = leerCadenaDelim(archivo, ',');
    archivo>>tipo;
    archivo.get();
    archivo>>precio;
    archivo.get();
    archivo>>cantVendidas;
    archivo.get();

    void **reg = new void* [8]; // uno mas que apuntara a nullptr y servira para linkear luego con insumos
    reg[0] = codigo;
    reg[1] = nombre;
    reg[2] = descripcion;
    reg[3] = new char{tipo};
    reg[4] = new bool{disponible};
    reg[5] = new double{precio};
    reg[6] = new int{cantVendidas};
    reg[7] = nullptr; // insumos

    bebida = reg;
    return true;
}


// B001,I001,10,g
void actualizarMenu(const char*nombArch, void*inventario, void*menu) {
    ifstream archivo(nombArch, ios::in);

    // variables auxiliares para la lectura
    char *codBebida, *codInsumo, *unidad;
    int cantidad;

    // punteros para la busqueda
    void **registroBebida = nullptr;
    void **registroInsumoInv = nullptr;


    // variable para el codigo de la bebida actual
    char codBebidaActual[10]="XYZ";
    int numInsumos=0, capInsumos=0;

    while (leerLineaInsumoBebidas(archivo, codBebida, codInsumo, cantidad, unidad)) {
        if (strcmp(codBebidaActual, codBebida) != 0) { // si son diferentes
            // buscamos el registro de la nueva bebida
            registroBebida = (void**)buscarBebida(menu, codBebida); // aqui vamos a actualizar
        }
    }


}