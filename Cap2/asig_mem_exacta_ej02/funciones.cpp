#include "funciones.h"
#include <cstring>

void cargarPacientes(const char*nombArch,Paciente *&pacientes) {
    // 10000001,Juan Perez,30,M
    ifstream archivo(nombArch, ios::in);

    Paciente pacienteAux[50];

    int cantDatos=0;
    while (archivo>>pacienteAux[cantDatos]) {
        cantDatos++;
    }
    pacientes = new Paciente[cantDatos+1];
    for (int i=0; i<cantDatos; i++) {
        pacientes[i] = pacienteAux[i];
    }
    pacientes[cantDatos] = {-1};
}

void cargarDoctores(const char*nombArch,Doctor *&doctores) {
    // 20000001,Miguel Garcia,CARDIOLOGIA
    ifstream archivo(nombArch, ios::in);

    Doctor doctorAux[50];

    int cantDatos=0;
    while (archivo>>doctorAux[cantDatos]) {
        cantDatos++;
    }
    doctores = new Doctor[cantDatos+1];
    for (int i=0; i<cantDatos; i++) {
        doctores[i] = doctorAux[i];
    }
    doctores[cantDatos] = {-1};
}

void cargarCitas(const char*nombArch, Cita *&citas) {
    ifstream archivo(nombArch, ios::in);

    Cita citaAux[210];

    int cantDatos=0;
    while (archivo>>citaAux[cantDatos]) {
        cantDatos++;
    }
    citas = new Cita[cantDatos+1];
    for (int i=0; i<cantDatos; i++) {
        citas[i] = citaAux[i];
    }
    citas[cantDatos] = {-1};
}

void procesarCitas(Clinica &clinica) {
    Paciente *pacientes = clinica.pacientes;
    Doctor *doctores = clinica.doctores;
    Cita *citas = clinica.citas;

    for (int i=0; citas[i].fecha!=-1; i++) {
        citas[i].paciente = obtenerInfoPaciente(citas[i].dniPaciente, pacientes);
        citas[i].doctor = obtenerInfoDoctor(citas[i].dniDoctor, doctores);

    }
}

const Paciente* obtenerInfoPaciente(int dni, const Paciente* pacientes) {
    for (int i=0; pacientes[i].dni!=-1; i++) {
        if (pacientes[i].dni == dni) {
            return &pacientes[i];
        }
    }
    return nullptr;
}

const Doctor* obtenerInfoDoctor(int dni, const Doctor* doctores) {
    for (int i=0; doctores[i].dni!=-1; i++) {
        if (doctores[i].dni == dni) {
            return &doctores[i];
        }
    }
    return nullptr;
}

Cita& operator!(Cita& cita) {
    cita.estado = CANCELADA;
    return cita;
}

bool operator>>(ifstream&archivo, Cita &citas) {
    // 2026-02-01,08:00,10000001,20000001,CANCELADA
    int dia,mes,anio,hora,min;
    char car;

    if (archivo>>anio) {
        archivo>>car>>mes>>car>>dia>>car>>hora>>car>>min>>car;
        citas.fecha = anio*10000+mes*1000+dia;
        citas.hora = hora*100+min;
        archivo>>citas.dniPaciente;
        archivo.get();
        archivo>>citas.dniDoctor;
        archivo.get();
        char*estado = leerCadena(archivo, '\n');
        citas.estado = convertirEstado(estado);
        delete[] estado;
        return true;
    }
    return false;
}

bool operator>>(ifstream&archivo, Doctor &doctor) {
    if (archivo>>doctor.dni) {
        archivo.get();
        doctor.nombre = leerCadena(archivo,',');
        char*especialidad = leerCadena(archivo,'\n');
        doctor.especialidad = convertirEspecialidad(especialidad);
        delete[] especialidad;
        return true;
    }
    return false;
}


Estado convertirEstado(char*estado) {
    if (strcmp(estado, "RESERVADA") == 0) return RESERVADA;
    else if (strcmp(estado, "CANCELADA") == 0) return CANCELADA;
    else return RESERVADA;
}

Especialidad convertirEspecialidad(char*especialidad) {
    if (strcmp(especialidad, "CARDIOLOGIA") == 0) return CARDIOLOGIA;
    else if (strcmp(especialidad, "DERMATOLOGIA") == 0) return DERMATOLOGIA;
    else if (strcmp(especialidad, "NEUROLOGIA") == 0) return NEUROLOGIA;
    else if (strcmp(especialidad, "PEDIATRIA") == 0) return PEDIATRIA;
    else if (strcmp(especialidad, "PSIQUIATRIA") == 0) return PSIQUIATRIA;
    else if (strcmp(especialidad, "TRAUMATOLOGIA") == 0) return TRAUMATOLOGIA;
    else if (strcmp(especialidad, "ENDOCRINOLOGIA") == 0) return ENDOCRINOLOGIA;
    else if (strcmp(especialidad, "GINECOLOGIA") == 0) return GINECOLOGIA;
    else if (strcmp(especialidad, "PSICOLOGIA") == 0) return PSICOLOGIA;
    else if (strcmp(especialidad, "ORTOPEDIA") == 0) return ORTOPEDIA;
    else return GENERAL;
}

bool operator>>(ifstream&archivo, Paciente &paciente) {
    if (archivo>>paciente.dni) {
        archivo.get();
        paciente.nombre = leerCadena(archivo,',');
        archivo>>paciente.edad;
        archivo.get();
        archivo>>paciente.genero;
        archivo.get();
        return true;
    }
    return false;
}

char *leerCadena(ifstream&archivo, char delim) {
    char auxiliar[250];
    char *ptrCadena;
    archivo.getline(auxiliar,250, delim);
    ptrCadena = new char[strlen(auxiliar)+1];
    strcpy(ptrCadena,auxiliar);
    return ptrCadena;
}

//
ostream& operator<<(ostream& os, const Doctor& doctor) {
    os << "DNI: " << doctor.dni << endl;
    os << "Nombre: " << doctor.nombre << endl;
    imprimirEspecialidad(os, doctor.especialidad);

    return os;
}

ostream& operator<<(ostream& os, const Paciente& paciente) {
    os << "DNI: " << paciente.dni << endl;
    os << "Nombre: " << paciente.nombre << endl;
    os << "Edad: " << paciente.edad << endl;
    os << "Genero: " << paciente.genero << endl;

    return os;
}
ostream& operator<<(ostream& os, const Cita& cita) {
    os << "==============================" << endl;
    os << "DATOS DEL CITA" << endl;
    os << "------------------------------" << endl;
    imprimirFecha(os, cita.fecha);
    imprimirHora(os, cita.hora);
    imprimirEstado(os, cita.estado);
    os << endl;
    os << "------------------------------" << endl;
    os << "DATOS DEL PACIENTE" << endl;
    os << "------------------------------" << endl;
    os << *cita.paciente << endl;
    os << "------------------------------" << endl;
    os << "DATOS DEL DOCTOR" << endl;
    os << "------------------------------" << endl;
    os << *cita.doctor << endl;
    os << "------------------------------" << endl;
    os << "==============================" << endl;

    return os;
}

ostream& operator<<(ostream& os, const Clinica& clinica) {
    for (int i = 0; clinica.citas[i].fecha != -1 ; i++) {
        os << clinica.citas[i] << endl;
    }
    return os;
}

void imprimirFecha(ostream& os, int fecha) {
    int anho = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;

    os << "Fecha: " << anho << "-";
    if (mes < 10) os << "0";
    os << mes << "-";
    if (dia < 10) os << "0";
    os << dia << endl;
}

void imprimirHora(ostream& os, int hora) {
    int horas = hora / 100;
    int minutos = hora % 100;

    os << "Hora: ";
    if (horas < 10) os << "0";
    os << horas << ":";
    if (minutos < 10) os << "0";
    os << minutos << endl;
}

void imprimirEstado(ostream& os, Estado estado) {
    switch (estado) {
        case RESERVADA:
            os << "Estado: " << "RESERVADA" << endl;
            break;
        case CANCELADA:
            os << "Estado: " << "CANCELADA" << endl;
            break;
        default:
            os << "Estado: " << "NA" << endl;
            break;;
    }
}

void imprimirEspecialidad(ostream& os, Especialidad especialidad) {
    switch (especialidad) {
        case CARDIOLOGIA:
            os << "Especialidad: " << "CARDIOLOGÍA" << endl;
            break;
        case DERMATOLOGIA:
            os << "Especialidad: " << "DERMATOLOGÍA" << endl;
            break;
        case NEUROLOGIA:
            os << "Especialidad: " << "NEUROLOGÍA" << endl;
            break;
        case PEDIATRIA:
            os << "Especialidad: " << "PEDIATRÍA" << endl;
            break;
        case PSIQUIATRIA:
            os << "Especialidad: " << "PSIQUIATRÍA" << endl;
            break;
        default:
            os << "Especialidad: " << "NA" << endl;
            break;
    }
}

