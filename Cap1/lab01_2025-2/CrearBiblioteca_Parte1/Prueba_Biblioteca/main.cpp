#include "library.h"
#include <iostream>

int main() {
    Alumnos a1, a2, a3;
    a1.codigo=1;
    a2.codigo=2;
    a3.codigo=3;

    Alumnos arreglo_alumnos[5];
    arreglo_alumnos[0] = a1;
    arreglo_alumnos[1] = a2;
    arreglo_alumnos[2] = a3;

    arreglo_alumnos[3].codigo=0; // esto pide el problema

    Alumnos a4;
    a4.codigo=4;

    //cout<<(arreglo_alumnos<=a4)<<endl;
    //cout<<(a1>0)<<endl;

    Cursos miCurso;
    miCurso.numpresencial = 0;
    miCurso.numsemipresencial = 0;
    miCurso.numvirtual = 0;
    miCurso.tipofinal = nullptr;

    Alumnos a5;
    a5.codigo=5;
    char nomb_temp[10] = "Juan";
    a5.nombre = new char[strlen(nomb_temp)+1];
    strcpy(a5.nombre, nomb_temp);
    a5.tipo='V';

    cout<<"Antes: "<<miCurso.numvirtual<<endl;

    miCurso+=a5;

    cout<<"Despues: "<<miCurso.numvirtual<<endl;

    miCurso++;

    cout<<miCurso.tipofinal<<endl;
    return 0;
}
