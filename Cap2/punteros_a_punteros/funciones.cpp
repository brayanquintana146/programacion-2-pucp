#include "funciones.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void cargarPacientes(const char*nombArch, int**&pacientes, char**&nombresPacientes) {
    ifstream archivo(nombArch, ios::in);

    int num=0, capacidad=0;
    pacientes = nullptr;
    nombresPacientes = nullptr;
    int *paciente;
    char *nombre;

    while (leerPaciente(archivo, paciente, nombre)) {
        if (num == capacidad) {
            incrementarPacientes(pacientes, nombresPacientes, num, capacidad);
        }
        pacientes[num] = paciente;
        nombresPacientes[num] = nombre;
        num++;
    }
    pacientes[num] = nullptr;
    nombresPacientes[num] = nullptr;
}

void cargarDoctores(const char*nombArch, int**&doctores, char**&nombresDoctores) {
    ifstream archivo(nombArch, ios::in);

    int num=0, capacidad=0;
    doctores = nullptr;
    nombresDoctores = nullptr;
    int *doctor;
    char *nombre;

    while (leerDoctor(archivo, doctor, nombre)) {
        if (num == capacidad) {
            incrementarDoctores(doctores, nombresDoctores, num, capacidad);
        }
        doctores[num] = doctor;
        nombresDoctores[num] = nombre;
        num++;
    }
    doctores[num] = nullptr;
    nombresDoctores[num] = nullptr;
}

void cargarCitas(const char*nombArch, int***&citas) {
    ifstream archivo(nombArch, ios::in);

    int num=0, capacidad=0;
    citas = nullptr;
    int **cita;

    while (leerCita(archivo, cita)) {
        if (num == capacidad) {
            incrementarCitas(citas, num, capacidad);
        }
        citas[num] = cita;
        num++;
    }
    citas[num] = nullptr;
}

void cargarCancelaciones(const char*nombArch, int***&cancelaciones) {
    ifstream archivo(nombArch, ios::in);

    int num=0, capacidad=0;
    cancelaciones = nullptr;
    int **cancelacion;

    while (leerCancelacion(archivo, cancelacion)) {
        if (num == capacidad) {
            incrementarCancelaciones(cancelaciones, num, capacidad);
        }
        cancelaciones[num] = cancelacion;
        num++;
    }
    cancelaciones[num] = nullptr;
}

void incrementarCancelaciones(int***&cancelaciones, int num, int&capacidad) {
    capacidad+=5;
    if (cancelaciones==nullptr) {
        cancelaciones = new int**[capacidad+1]{};
    }
    else {
        int***auxCancel = new int**[capacidad+1]{};
        for (int i=0; i<num; i++) {
            auxCancel[i] = cancelaciones[i];
        }
        delete[] cancelaciones;
        cancelaciones = auxCancel;
    }
}

bool leerCancelacion(ifstream&archivo, int**&cancelacion) {
    // 2026-02-01,08:00,10000001,20000001
    int anho;
    if (!(archivo >> anho)) {
        return false;
    }

    archivo.ignore();
    int mes, dia;
    archivo >> mes;
    archivo.ignore();
    archivo >> dia;
    int fecha = anho * 10000 + mes * 100 + dia;

    archivo.ignore();
    int hora, minuto;
    archivo >> hora;
    archivo.ignore();
    archivo >> minuto;
    int horaCompleta = hora * 100 + minuto;

    archivo.ignore();
    int dniPaciente, dniDoctor;
    archivo >> dniPaciente;
    archivo.ignore();
    archivo >> dniDoctor;
    if (archivo.peek() == '\n') archivo.get();

    cancelacion = new int*[1];
    cancelacion[0] = new int[4]{fecha, horaCompleta, dniPaciente, dniDoctor};
    return true;
}

void incrementarCitas(int***&citas, int num, int &capacidad) {
    capacidad+=5;
    if (citas==nullptr) {
        citas = new int**[capacidad+1]{};
    }
    else {
        int ***auxCitas = new int**[capacidad+1]{};
        for (int i=0; i<num; i++) {
            auxCitas[i] = citas[i];
        }
        delete[] citas;
        citas = auxCitas;
    }
}

bool leerCita(ifstream&archivo, int**&cita) {
    // 2026-02-01,08:00,10000001,20000001,0
    int anho;
    if (!(archivo >> anho)) {
        return false;
    }

    archivo.ignore();
    int mes, dia;
    archivo >> mes;
    archivo.ignore();
    archivo >> dia;
    int fecha = anho * 10000 + mes * 100 + dia;

    archivo.ignore();
    int hora, minuto;
    archivo >> hora;
    archivo.ignore();
    archivo >> minuto;
    int horaCompleta = hora * 100 + minuto;

    archivo.ignore();
    int dniPaciente, dniDoctor;
    archivo >> dniPaciente;
    archivo.ignore();
    archivo >> dniDoctor;
    archivo.ignore();

    int estado;
    archivo >> estado;
    if (archivo.peek() == '\n') archivo.get();

    cita = new int*[3];
    cita[0] = new int[2]{fecha, horaCompleta};
    cita[1] = new int[2]{dniPaciente, dniDoctor};
    cita[2] = new int[1]{estado};
    return true;
}


bool leerDoctor(ifstream&archivo, int*&doctor, char*&nombre) {
    // 20000001,Miguel Garcia,0
    int dni, especialidad;
    if (!(archivo>>dni)) {
        return false;
    }
    archivo.get();
    nombre = leerCompletoDelim(archivo, ',');
    archivo>>especialidad;
    archivo.get();

    doctor = new int[2]{dni, especialidad};
    return true;
}

void incrementarDoctores(int**&doctores, char**&nombresDoctores, int num, int&capacidad) {
    capacidad+=5;
    int** auxDoctores;
    char** auxNombres;

    if (doctores == nullptr) {
        doctores=new int*[capacidad+1]{};
        nombresDoctores=new char*[capacidad+1]{};
    }
    else {
        auxDoctores = new int*[capacidad+1]{};
        auxNombres = new char*[capacidad+1]{};
        for (int i=0; i<num; i++) {
            auxDoctores[i] = doctores[i];
            auxNombres[i] = nombresDoctores[i];
        }
        delete[] doctores;
        delete[] nombresDoctores;
        doctores = auxDoctores;
        nombresDoctores = auxNombres;
    }
}

void incrementarPacientes(int**&pacientes, char**&nombresPacientes, int num, int&capacidad) {
    capacidad+=5;
    int** auxPacientes;
    char** auxNombres;

    if (pacientes == nullptr) {
        pacientes=new int*[capacidad+1]{};
        nombresPacientes=new char*[capacidad+1]{};
    }
    else {
        auxPacientes = new int*[capacidad+1]{};
        auxNombres = new char*[capacidad+1]{};
        for (int i=0; i<num; i++) {
            auxPacientes[i] = pacientes[i];
            auxNombres[i] = nombresPacientes[i];
        }
        delete[] pacientes;
        delete[] nombresPacientes;
        pacientes = auxPacientes;
        nombresPacientes = auxNombres;
    }

}

bool leerPaciente(ifstream&archivo, int*&paciente, char*&nombre) {
    // 10000001,Juan Perez,30,M
    int dni, edad;
    char sexo;

    if (!(archivo>>dni)) {
        return false;
    }

    archivo.get();
    nombre = leerCompletoDelim(archivo, ',');
    archivo>>edad;
    archivo.get();
    archivo>>sexo;
    archivo.get();

    paciente = new int[3]{dni, edad, int(sexo)}; // creamos espacio para tres enteros al que paciente va a apuntar
    return true;

}

char *leerCompletoDelim(ifstream& archivo, char delim) {
    char ptrAux[100], *ptrCadena;
    archivo.getline(ptrAux,100, delim);
    ptrCadena = new char[strlen(ptrAux)+1];
    strcpy(ptrCadena, ptrAux);
    return ptrCadena;
}

void cancelarCitas(int ***cancelaciones, int***citas) {
    for (int i=0; cancelaciones[i]; i++) {
        int **cancelacion = cancelaciones[i];
        int *datosCancela = cancelacion[0];

        int **cita = obtenerCitaPorCriterio(citas, datosCancela);
        if (cita != nullptr) {
            cancelarEstaCita(cita);
        }
    }
}

void cancelarEstaCita(int**&cita) {
    int *estado = cita[2];
    estado[0] = 0;
}

int **obtenerCitaPorCriterio(int***citas, int*datosCancela) {
    int fecha = datosCancela[0];
    int hora = datosCancela[1];
    int dniPaciente = datosCancela[2];
    int dniDoctor = datosCancela[3];

    for (int i=0; citas[i]; i++) {
        int **cita = citas[i];
        int *fechaHora = cita[0];
        int *dniPacienteDoctor = cita[1];

        int fechaCita = fechaHora[0];
        int horaCita = fechaHora[1];
        int dniPacienteCita = dniPacienteDoctor[0];
        int dniDoctorCita = dniPacienteDoctor[1];

        if (fechaCita == fecha && horaCita == hora
            && dniPacienteCita == dniPaciente
            && dniDoctorCita == dniDoctor) {
            return cita;
        }
    }
    return nullptr;
}


