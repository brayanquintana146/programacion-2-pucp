//
// Created by Brayan on 3/05/2026.
//

#ifndef EJERCICIO02_FUNCIONES_H
#define EJERCICIO02_FUNCIONES_H
#include <fstream>
#include "funciones.h"
#include <cstring>
#include "enum.h"

using namespace std;

void cargarDatos(void*& clinica,
                 const char* archivoPacientes,
                 const char* archivoDoctores,
                 const char* archivoCitas,
                 const char* archivoCancelaciones);
void cargarRegistros(const char*archivoPacientes, void*&datos, bool (*leerRegistro)(ifstream&, void*&));
void incrementarCapacidad(void**&registros, int num, int&capacidad);
bool leerPaciente(ifstream&archivo, void*&paciente);
char *leerCadenaDelim(ifstream&archivo, char delim);
bool leerDoctores(ifstream&archivo, void*&doctores);
void cargarEventos(const char*nombreArchivo, void*&clinica, int pos, bool(*leerEvento)(ifstream&, void*&, int&),
    void (*liberarEventoNoAsociado)(void*&));
void * buscarPaciente(int dniPaciente, void*pacientes);
void agregarRegistroExacto(void**&eventosPaciente, void*dato);
bool leerCita(ifstream&archivo, void*&cita, int&dniPaciente);
void liberarCita(void*&cita);
bool leerCancelacion(ifstream&archivo, void*&cancelacion, int&dniPaciente);
void liberarCancelacion(void*&cancelacion);
void cancelarCitas(void*&clinica);
void procesarCancelacionesPaciente(void**paciente);
void aplicarCancelacionPaciente(void**paciente, void*cancelacion);
void* buscarCitaPaciente(void** paciente, int fecha, int hora, int dniDoctor);
bool esMismaCita(const void* cita, int fecha, int hora, int dniDoctor);
void cancelarCita(void*& cita);
void imprimirReporte(ofstream& archivo, const void* clinica);
void imprimirCitasPaciente(ofstream& archivo, const void* paciente, const void* doctores);
void imprimirDetalleCita(ofstream& archivo, const void* paciente, const void* cita);
void imprimirCita(ofstream& archivo, int fecha, int hora, int estado);
void imprimirPaciente(ofstream& archivo, const void* paciente);
void imprimirDoctor(ofstream& archivo, const void* doctor);
void imprimirFecha(ostream& os, int fecha);
void imprimirHora(ostream& os, int hora);
void imprimirEstado(ostream& os, int estado);
void imprimirEspecialidad(ostream& os, int especialidad);
void* buscarDoctor(int dniDoctor, const void* doctores);



#endif //EJERCICIO02_FUNCIONES_H
