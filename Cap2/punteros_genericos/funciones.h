#ifndef PUNTEROS_GENERICOS_FUNCIONES_H
#define PUNTEROS_GENERICOS_FUNCIONES_H

#include "enum.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>

using namespace std;

void cargarDatos(void*&clinica,const char*nombArchPaci,const char*nombArchDoct,const char*nombArchCitas,
    const char*nombArchCancela);
void cargarPacientes(const char*nombArchPaci, void*&pacientes);
bool leerPaciente(ifstream&archPacientes,void*&paciente);
char *leerCadenaDelim(ifstream& archPacientes,char delim);
void incrementarCapacidad(void**&registros, int num, int&capacidad);
void cargarDoctores(const char*nombArchDoct, void*&doctores);
bool leerDoctor(ifstream&archDocs, void*&doctor);
void cargarCitas(const char*nombArchCitas,void*clinica);
bool leerCita(ifstream&archCitas, void*&cita, int&dniPaciente);
void *buscarPaciente(int dniPaciente, const void*pacientes);
void agregarRegistroExacto(void**&registros, void*registro);



#endif //PUNTEROS_GENERICOS_FUNCIONES_H
