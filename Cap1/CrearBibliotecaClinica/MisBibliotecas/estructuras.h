#ifndef OPERADORES_CLINICA_ESTRUCTURAS_H
#define OPERADORES_CLINICA_ESTRUCTURAS_H
#include "enums.h"

struct Paciente {
    int dni;
    int edad;
    char genero;
};

struct Doctor {
    int dni;
    Especialidad especialidad;
};

struct Cita {
    int fecha;
    int hora;
    Paciente paciente;
    Doctor doctor;
    Estado estado;
};

struct Clinica {
    Paciente *pacientes;
    Doctor *doctores;
    Cita *citas;
    int numPacientes;
    int numDoctors;
    int numCitas;
};

#endif //OPERADORES_CLINICA_ESTRUCTURAS_H
