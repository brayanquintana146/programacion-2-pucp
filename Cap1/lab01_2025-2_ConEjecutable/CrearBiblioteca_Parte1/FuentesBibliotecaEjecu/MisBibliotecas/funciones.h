#ifndef FUENTES__BIBIOTECA_2025_2_LIBRARY_H
#define FUENTES__BIBIOTECA_2025_2_LIBRARY_H

#include "Estructuras.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

void operator>>(ifstream &arch, Cursos &curso);
char *leerConDelimitador(ifstream &arch, char delim);
void operator>>(ifstream &arch, Alumnos &alumno);
bool operator>(Alumnos &alumno, int codigoCurso);
bool operator>(Cursos &curso, char* codigoCurso);
void operator+=(Cursos &curso, Alumnos &alumno);
int operator<=(Alumnos *arrAlumnos, Alumnos &alumno);
int operator>=(Cursos *arrCursos, Cursos &curso);
void operator++(Cursos &curso, int);
void operator<<(ofstream&arch, Cursos &curso);



#endif // FUENTES__BIBIOTECA_2025_2_LIBRARY_H
