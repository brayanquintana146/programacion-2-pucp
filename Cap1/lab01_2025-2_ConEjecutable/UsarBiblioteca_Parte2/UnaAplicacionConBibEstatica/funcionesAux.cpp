#include "funcionesAux.h"

void cargarAlumnos(ifstream &archAlumno, Alumnos *arrAlummnos) {
    int i=0;
    while(true) {
        archAlumno>>arrAlummnos[i];
        if (archAlumno.eof()) break;
        i++;
    }
    arrAlummnos[i].codigo=0; // pide en el enunciado
}

void cargarCursos(ifstream&archCurso, Cursos *arrCursos) {
    int i=0;
    while(true) {
        archCurso>>arrCursos[i];
        if (archCurso.eof()) break;
        i++;
    }
    arrCursos[i].codigo=nullptr;
}

void cargarMatricula(ifstream&archMatr, Alumnos *arrAlummnos, Cursos *arrCursos) {
    Alumnos alumnoAux;
    Cursos cursoAux;
    int id_alumno, id_curso;

    while(true) {
        cursoAux.codigo=leerConDelimitador(archMatr, ',');
        if (archMatr.eof()) break;
        archMatr>>alumnoAux.codigo;
        archMatr.get();

        id_alumno = (arrAlummnos<=alumnoAux);
        id_curso = (arrCursos>=cursoAux);

        arrCursos[id_curso]+=arrAlummnos[id_alumno];
    }
}

void actualizarCursos(Cursos *arrCursos) {
    int i=0;
    while(true) {
        if (arrCursos[i].codigo==nullptr) break;
        arrCursos[i]++;
        i++;
    }
}

void crearReporte(ofstream& archReporte, Cursos*arrCursos) {
    int i=0;
    while(true) {
        if (arrCursos[i].codigo==nullptr) break;
        archReporte<<arrCursos[i];

        i++;
    }
}