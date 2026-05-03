#include <cstdlib>
#include "funciones.h"
using namespace std;
int main(int argc, char** argv) {
    void *inventario, *menu;

    cargarInventario("inventario.csv", inventario);
    // void **arregloInventario = (void**)inventario;
    // for (int i = 0; arregloInventario[i]; i++) {
    //     void **insumoActual = (void**)(arregloInventario[i]);
    //
    //     char *codigo = (char*)(insumoActual[0]);
    //     int cantidad = *(int*)(insumoActual[2]);
    //     cout << cantidad << endl;
    // }

    cargarMenu("menu.csv", menu);
    void **arregloMenu = (void**)menu;
    // for (int i = 0; arregloMenu[i]; i++) {
    //     void **bebidaActual = (void**)(arregloMenu[i]);
    //
    //     char *codigo = (char*)(bebidaActual[0]);
    //     int cantVentasEstim = *(int*)(bebidaActual[6]);
    //     cout << codigo << endl;
    // }


    actualizarMenu("insumos-bebidas.csv", inventario, menu);
    // reporteMenu("menu.txt", menu);




    return 0;
}