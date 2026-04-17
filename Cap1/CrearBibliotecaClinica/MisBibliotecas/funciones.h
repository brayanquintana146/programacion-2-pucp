#ifndef OPERADORES_CLINICA_FUNCIONES_H
#define OPERADORES_CLINICA_FUNCIONES_H
#include <iostream>
#include "enums.h"
#include "estructuras.h"

using namespace std;


void cargarPacientes(Clinica&);
void cargarDoctores(Clinica&);
void cargarCitas(Clinica&);

Clinica& operator+=(Clinica&, Paciente&);
Clinica& operator+=(Clinica&, Doctor&);
Clinica& operator+=(Clinica&, Cita&);

bool operator<(Cita&, Cita&);
Cita& operator!(Cita&);

ostream& operator<<(ostream&, const Paciente&);
ostream& operator<<(ostream&, const Doctor&);
ostream& operator<<(ostream&, const Cita&);
ostream& operator<<(ostream&, const Clinica&);

void insertarOrdenado(Clinica&, Cita&);
void imprimirFecha(ostream&, int);
void imprimirHora(ostream&, int);
void imprimirEstado(ostream&, Estado);
void imprimirEspecialidad(ostream&, Especialidad);

#endif //OPERADORES_CLINICA_FUNCIONES_H
