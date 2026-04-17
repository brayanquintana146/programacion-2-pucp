#include "funciones.h"

#include <iomanip>
#include <cstring>

// INF263,Algoritmia,3.75,35030611,INGA_FLORES_CESAR_ADOLFO
void operator>>(ifstream &arch, Cursos &curso) {
    int ignorar; // se usa para ignorar el codigo del docente
    curso.codigo = leerConDelimitador(arch, ',');
    curso.nombre = leerConDelimitador(arch, ',');
    arch>>curso.creditos;
    arch.get();
    arch>>ignorar;
    arch.get();
    curso.docente = leerConDelimitador(arch, '\n');

    // inicializamos los indices de los tres arreglos alumnos
    curso.numpresencial=0;
    curso.numsemipresencial=0;
    curso.numvirtual=0;
}

char *leerConDelimitador(ifstream &arch, char delim) {
    char *ptrCadena, ptrAux[100];
    arch.getline(ptrAux, 100, delim);
    ptrCadena = new char[strlen(ptrAux) + 1];
    strcpy(ptrCadena, ptrAux);
    return ptrCadena;
}

// 202111260,GORDILLO/CASTRO/RONAL,P

void operator>>(ifstream &arch, Alumnos &alumno) {
    arch>>alumno.codigo;
    arch.get();
    alumno.nombre = leerConDelimitador(arch, ',');
    arch>>alumno.tipo;
    arch.get();
}

bool operator>(Alumnos &alumno, int codigoCurso) {
    return alumno.codigo == codigoCurso;
}

bool operator>(Cursos &curso, char* codigoCurso) {
    return strcmp(curso.codigo, codigoCurso) == 0;
}

void operator+=(Cursos &curso, Alumnos &alumno) {
    // antes debimos inicializar los indices
    if (alumno.tipo == 'P') {
        curso.presencial[curso.numpresencial] = alumno;
        curso.numpresencial++;
    }
    else if (alumno.tipo == 'S') {
        curso.semipresencial[curso.numsemipresencial] = alumno;
        curso.numsemipresencial++;
    }
    else {
        curso.vvirtual[curso.numvirtual] = alumno;
        curso.numvirtual++;
    }
}

int operator<=(Alumnos *arrAlumnos, Alumnos &alumno) {
    for (int i=0; arrAlumnos[i].codigo; i++) {
        if (arrAlumnos[i].codigo == alumno.codigo) {
            return i;
        }
    }
    return -1;
}

int operator>=(Cursos *arrCursos, Cursos &curso) {
    for (int i=0; arrCursos[i].codigo != nullptr; i++) {
        if (strcmp(arrCursos[i].codigo, curso.codigo)==0) {
            return i;
        }
    }
    return -1;
}

void operator++(Cursos &curso, int) {
    int total = curso.numpresencial + curso.numvirtual + curso.numsemipresencial;
    double porce_pres = curso.numpresencial*100/double(total);

    if (total==0) return; // por si totavia no hay aummnos

    if (porce_pres>=50) {
        char texto1[40]="La clase se dictara en aula";
        curso.tipofinal = new char[strlen(texto1)+1];
        strcpy(curso.tipofinal, texto1);
    }
    else {
        char texto2[40]="La clase se dictara 100% virtual";
        curso.tipofinal = new char[strlen(texto2)+1];
        strcpy(curso.tipofinal, texto2);
    }
}

void operator<<(ofstream&arch, Cursos &curso) {
    arch<<left<<setw(10)<<curso.codigo<<curso.nombre<<endl;
    arch<<curso.docente<<endl;
    arch<<left<<setw(28)<<"Alumnos presenciales:"
        <<right<<setw(5)<<curso.numpresencial<<endl;

    arch<<left<<setw(28)<<"Alumnos semipresenciales:"
        <<right<<setw(5)<<curso.numsemipresencial<<endl;

    arch<<left<<setw(28)<<"Alumnos virtuales:"
        <<right<<setw(5)<<curso.numvirtual<<endl;
    arch<<curso.tipofinal<<endl;
}