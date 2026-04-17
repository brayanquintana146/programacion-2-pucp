//
// Created by Brayan on 16/04/2026.
//

#ifndef ASIG_MEM_EXACTA_EJ02_FUNCIONES_H
#define ASIG_MEM_EXACTA_EJ02_FUNCIONES_H

#include <iostream>
#include <fstream>

#include "enums.h"
#include "estructuras.h"

using namespace std;

void cargarPacientes(const char*nombArch,Paciente *&pacientes);
char *leerCadena(ifstream&archivo, char delim);
bool operator>>(ifstream&archivo, Paciente &paciente);
void cargarDoctores(const char*nombArch,Doctor *&doctores);
bool operator>>(ifstream&archivo, Doctor &doctor);
void cargarCitas(const char*nombArch, Cita *&citas);
bool operator>>(ifstream&archivo, Cita &citas);
void procesarCitas(Clinica &clinica);
const Paciente* obtenerInfoPaciente(int dni, const Paciente* pacientes);
const Doctor* obtenerInfoDoctor(int dni, const Doctor* doctores);
Cita& operator!(Cita& cita);
Especialidad convertirEspecialidad(char*especialidad);
Estado convertirEstado(char*estado);
//
ostream& operator<<(ostream& os, const Doctor& doctor);
ostream& operator<<(ostream& os, const Cita& cita);
ostream& operator<<(ostream& os, const Clinica& clinica);
ostream& operator<<(ostream& os, const Paciente& paciente);
void imprimirFecha(ostream& os, int fecha);
void imprimirHora(ostream& os, int hora);
void imprimirEstado(ostream& os, Estado estado);
void imprimirEspecialidad(ostream& os, Especialidad especialidad);



#endif //ASIG_MEM_EXACTA_EJ02_FUNCIONES_H
