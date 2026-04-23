#include <fstream>
using namespace std;


#ifndef PUNTEROS_A_PUNTEROS_FUNCIONES_H
#define PUNTEROS_A_PUNTEROS_FUNCIONES_H

void cargarPacientes(const char*nombArch, int**&pacientes, char**&nombresPacientes);
void incrementarPacientes(int**&pacientes, char**&nombresPacientes, int num, int&capacidad);
bool leerPaciente(ifstream&archivo, int*&paciente, char*&nombre);
char *leerCompletoDelim(ifstream& archivo, char delim);
bool leerDoctor(ifstream&archivo, int*&doctor, char*&nombre);
void incrementarDoctores(int**&doctores, char**&nombresDoctores, int num, int&capacidad);
void cargarDoctores(const char*nombArch, int**&doctores, char**&nombresDoctores);
void cargarCitas(const char*nombArch, int***&citas);
bool leerCita(ifstream&archivo, int**&cita);
void incrementarCitas(int***&citas, int num, int &capacidad);
void cargarCancelaciones(const char*nombArch, int***&cancelaciones);
bool leerCancelacion(ifstream&archivo, int**&cancelacion);
void incrementarCancelaciones(int***&cancelaciones, int num, int&capacidad);
void cancelarCitas(int ***cancelaciones, int***citas);
int **obtenerCitaPorCriterio(int***citas, int*datosCancela);
void cancelarEstaCita(int**&cita);


#endif //PUNTEROS_A_PUNTEROS_FUNCIONES_H
