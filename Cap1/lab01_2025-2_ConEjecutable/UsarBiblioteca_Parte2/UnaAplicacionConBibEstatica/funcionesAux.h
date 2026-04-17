#ifndef UNAAPLICACIONCONBIBESTATICA_FUNCIONESAUX_H
#define UNAAPLICACIONCONBIBESTATICA_FUNCIONESAUX_H

#include "MisBibliotecas/funciones.h"

void cargarAlumnos(ifstream &archAlumno, Alumnos *arrAlummnos);
void cargarCursos(ifstream&archCurso, Cursos *arrCursos);
void cargarMatricula(ifstream&archMatr, Alumnos *arrAlummnos, Cursos *arrCursos);
void actualizarCursos(Cursos *arrCursos);
void crearReporte(ofstream& archReporte, Cursos*arrCursos);

#endif //UNAAPLICACIONCONBIBESTATICA_FUNCIONESAUX_H
