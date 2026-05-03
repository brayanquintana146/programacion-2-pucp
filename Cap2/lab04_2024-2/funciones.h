#ifndef LAB04_2024_2_FUNCIONES_H
#define LAB04_2024_2_FUNCIONES_H
#include "funciones.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

void cargarInventario(const char*nombArch, void*&inventario);
bool leerInventario(ifstream&archivo, void*&insumo);
char *leerCadenaDelim(ifstream&archivo, char delim);
void incrementarEspacio(void**&registros, int num, int&capacidad);
void cargarMenu(const char*nombArch, void*&menu);
bool leerMenu(ifstream&archivo, void*&bebida);

#endif //LAB04_2024_2_FUNCIONES_H
