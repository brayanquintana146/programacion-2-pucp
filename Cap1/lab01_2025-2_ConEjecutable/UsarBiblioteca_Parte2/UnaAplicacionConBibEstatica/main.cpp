#include "MisBibliotecas/funciones.h"
#include "funcionesAux.h"
#include <iostream>

int main() {
    ifstream archAlumno("Alumnos.csv", ios::in);
    if (not archAlumno.is_open()) {
        cout << "Error al abrir el archivo Alumnos.csv" << endl;
        exit(1);
    }
    ifstream archCurso("Cursos.csv", ios::in);
    if (not archAlumno.is_open()) {
        cout << "Error al abrir el archivo Cursos.csv" << endl;
        exit(1);
    }
    ifstream archMatr("Matricula.csv", ios::in);
    if (not archAlumno.is_open()) {
        cout << "Error al abrir el archivo Matricula.csv" << endl;
        exit(1);
    }
    ofstream archReporte("Reporte.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo Reporte.csv" << endl;
        exit(1);
    }



    Alumnos arrAlummnos[80];
    cargarAlumnos(archAlumno, arrAlummnos);

    Cursos arrCursos[10];
    cargarCursos(archCurso, arrCursos);

    cargarMatricula(archMatr, arrAlummnos, arrCursos);

    actualizarCursos(arrCursos);

    crearReporte(archReporte, arrCursos);

    return 0;
}
